#include "Chunk.hpp"

#include <glm/glm.hpp>

#include "ChunkMap.hpp"
#include "World.hpp"
#include "world_utils.hpp"
#include "ChunkMesh.hpp"
#include "../Utils/PerlinNoise.hpp"

namespace mc
{
	Chunk::Chunk(World& world, ChunkMap &map, glm::ivec2 position) : 
													  m_world(world),
													  m_map(map),
													  m_position(position),
													  m_mesh(nullptr)
	{
		generateTerrain();
		generateDecorations();
	}

	Chunk::~Chunk()
	{
	}

	Block Chunk::qGetBlock(const glm::ivec3 &pos) const
	{
		return m_blocks[pos.x][pos.y][pos.z];
	}

	Block Chunk::getBlock(const glm::ivec3 &pos) const
	{
		if (pos.z < 0 || pos.z >= CHUNK_SIZE || pos.x < 0 || pos.x >= CHUNK_SIZE || pos.y < 0 || pos.y >= CHUNK_SIZE)
			// return m_world.getBlock(toGlobalBlockPosition(m_position, pos));
			return Block::Air;
		return qGetBlock(pos);
	}

	void Chunk::generateMesh()
	{
		m_mesh = std::make_unique<ChunkMesh>(*this);
	}

	void Chunk::draw(ChunkMeshPart part) const
	{
		if (m_mesh == nullptr)
			return;
		if (m_mesh->isGenerated() == false)
			m_mesh->generateMesh();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, getWorldPosition());
		m_world.getChunkShader().setUniform("model", model);
		m_mesh->draw(part);
	}

	int Chunk::getHeight(int x, int z) const
	{
		const static siv::PerlinNoise::seed_type seed = 123456u;
		const static siv::PerlinNoise perlin{seed};

		return glm::clamp((int)(perlin.octave2D_01((x + (float)m_position.x * CHUNK_SIZE) * 0.02f, (z + (float)m_position.y * CHUNK_SIZE) * 0.02f, 4, 0.35f) * CHUNK_SIZE), MIN_HEIGHT, MAX_HEIGHT);
	}

	void Chunk::generateTerrain()
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				int max_height = getHeight(x, z);
				int stone_height = max_height - 3;
				for (int y = 0; y < CHUNK_SIZE; y++)
				{
					Block block = Block::Air;
					if (y < stone_height)
						block = Block::Stone;
					else if (y < max_height)
						block = Block::Dirt;
					else if (y == max_height)
					{
						if (max_height < OCEAN_LEVEL + 1)
							block = Block::Sand;
						else
							block = Block::Grass;
					}
					else if (y >= MIN_HEIGHT && y < OCEAN_LEVEL)
					{
						block = Block::Water;
					}
					else
						block = Block::Air;
					m_blocks[x][y][z] = block;
				}
			}
		}
	}

	void Chunk::generateDecorations()
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				int max_height = getHeight(x, z);
				if (max_height > OCEAN_LEVEL + 2)
				{
					if (rand() % 125 > 123)
						generateTree(x, max_height + 1, z);
					else if (rand() % 100 > 90)
						m_blocks[x][max_height + 1][z] = Block::TallGrass;
					else if (rand() % 100 > 97)
					{
						if (rand() % 3 > 1)
							m_blocks[x][max_height + 1][z] = Block::YellowFlower;
						else
							m_blocks[x][max_height + 1][z] = Block::Rose;
					}
				}
			}
		}
	}

	void Chunk::generateTree(int x, int y, int z)
	{
		m_blocks[x][y][z] = Block::Wood;
		int height = (rand() % 3) + 3;

		for (int i = 0; i < height; i++)
		{
			m_blocks[x][y + i][z] = Block::Wood;
		}

		int leave_height = (rand() % 2) + 2;
		for (int xx = (x - 2); xx <= (x + 2); xx++)
		{
			for (int zz = (z - 2); zz <= (z + 2); zz++)
			{
				for (int yy = (y + height); yy <= (y + height + 1); yy++)
				{
					int c = 0;
					c += xx == (x - 2) || xx == (x + 2);
					c += zz == (z - 2) || zz == (z + 2);
					bool corner = c == 2;

					if ((!(xx == x && zz == z) || yy > (y + height)) &&
						!(corner && yy == (y + height + 1) && rand() % 100 > 40))
					{
						if (yy < CHUNK_SIZE - 1 && xx < CHUNK_SIZE - 1 && zz < CHUNK_SIZE - 1 && xx > 0 && zz > 0 && yy > 0)
							m_blocks[xx][yy][zz] = Block::Leaves;
					}
				}
			}
		}

		for (int xx = (x - 1); xx <= (x + 1); xx++)
		{
			for (int zz = (z - 1); zz <= (z + 1); zz++)
			{
				for (int yy = (y + height + 2); yy <= (y + height + leave_height); yy++)
				{
					int c = 0;
					c += xx == (x - 1) || xx == (x + 1);
					c += zz == (z - 1) || zz == (z + 1);
					bool corner = c == 2;

					if (!(corner && yy == (y + height + leave_height) && rand() % 100 > 20))
					{
						if (yy < CHUNK_SIZE - 1 && xx < CHUNK_SIZE - 1 && zz < CHUNK_SIZE - 1 && xx > 0 && zz > 0 && yy > 0)
							m_blocks[xx][yy][zz] = Block::Leaves;
					}
				}
			}
		}
	}
}
