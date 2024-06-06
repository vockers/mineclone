#include "World/Chunk.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include "World/ChunkMap.hpp"
#include "World/World.hpp"
#include "World/world_utils.hpp"
#include "World/ChunkMesh.hpp"
#include "Utils/PerlinNoise.hpp"

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

    BlockID Chunk::qGetBlock(int x, int y, int z) const
	{
		return m_blocks[z * CHUNK_AREA + y * CHUNK_SIZE + x];
	}

	BlockID Chunk::qGetBlock(const glm::ivec3 &pos) const
	{
		return qGetBlock(pos.x, pos.y, pos.z);
	}

    BlockID Chunk::getBlock(int x, int y, int z) const
	{
		if (!checkBounds(x, y, z))
			return BlockID::Air;

		return qGetBlock(x, y, z);
	}

    BlockID Chunk::getBlock(const glm::ivec3 &pos) const
	{
		return getBlock(pos.x, pos.y, pos.z);
	}

    void Chunk::qSetBlock(int x, int y, int z, BlockID block)
	{
		m_blocks[z * CHUNK_AREA + y * CHUNK_SIZE + x] = block;
	}

	void Chunk::setBlock(int x, int y, int z, BlockID block)
	{
		if (!checkBounds(x, y, z))
			return;
		
		qSetBlock(x, y, z, block);
	}

    void Chunk::generateMesh()
	{
		m_mesh = std::make_unique<ChunkMesh>(*this);
	}

    void Chunk::draw(ChunkMesh::Part part) const
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

	int Chunk::getTopBlock(int x, int z) const
	{
		return m_top_blocks[z * CHUNK_SIZE + x];
	}

	bool Chunk::checkBounds(int x, int y, int z) const
	{
		return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE;
	}

	void Chunk::generateTerrain()
	{
		const static siv::PerlinNoise::seed_type seed = World::SEED;
		const static siv::PerlinNoise perlin{seed};

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				int max_height = glm::clamp((int)(perlin.octave2D_01((x + (float)m_position.x * CHUNK_SIZE) * 0.02f, (z + (float)m_position.y * CHUNK_SIZE) * 0.02f, 4, 0.35f) * CHUNK_SIZE), MIN_HEIGHT, MAX_HEIGHT);
				m_top_blocks[z * CHUNK_SIZE + x] = max_height;
				int stone_height = max_height - 3;
				for (int y = 0; y < CHUNK_SIZE; y++)
				{
					BlockID block = BlockID::Air;
					if (y < stone_height)
						block = BlockID::Stone;
					else if (y < max_height)
						block = BlockID::Dirt;
					else if (y == max_height)
					{
						if (max_height < OCEAN_LEVEL + 1)
							block = BlockID::Sand;
						else
							block = BlockID::Grass;
					}
					else if (y >= MIN_HEIGHT && y < OCEAN_LEVEL)
					{
						block = BlockID::Water;
					}
					else
						block = BlockID::Air;
					qSetBlock(x, y, z, block);
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
				int max_height = getTopBlock(x, z);
				if (max_height > OCEAN_LEVEL + 2)
				{
					if (rand() % 125 > 123)
						generateTree(x, max_height + 1, z);
					else if (rand() % 100 > 90)
						qSetBlock(x, max_height + 1, z, BlockID::TallGrass);
					else if (rand() % 100 > 97)
					{
						if (rand() % 3 > 1)
							qSetBlock(x, max_height + 1, z, BlockID::YellowFlower);
						else
							qSetBlock(x, max_height + 1, z, BlockID::Rose);
					}
				}
			}
		}
	}

	void Chunk::generateTree(int x, int y, int z)
	{
		setBlock(x, y, z, BlockID::Wood);
		int height = (rand() % 3) + 3;

		for (int i = 0; i < height; i++)
		{
			setBlock(x, y + i, z, BlockID::Wood);
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
						setBlock(xx, yy, zz, BlockID::Leaves);
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
						setBlock(xx, yy, zz, BlockID::Leaves);
				}
			}
		}
	}
}
