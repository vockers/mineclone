#include "Chunk.hpp"

#include <iostream>

#include "ChunkMesh.hpp"
#include "../Utils/PerlinNoise.hpp"

Chunk::Chunk(glm::ivec2 position) : 
	m_position(position),
	m_mesh(nullptr)
{
	const static siv::PerlinNoise::seed_type seed = 123456u;
	const static siv::PerlinNoise perlin{seed};

	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			float result = perlin.octave2D_01((x + (float)position.x * CHUNK_SIZE) * 0.01f, (z + (float)position.y * CHUNK_SIZE) * 0.01f, 4);
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				BlockType block = BlockType::Air;
				if (y < result * 32)
					block = BlockType::Grass;
				if (y < result * 32 && result < 0.3f)
					block = BlockType::Dirt;
				if (y < result * 5)
					block = BlockType::Stone;

				m_blocks[x][y][z] = block;
			}
		}
	}
}

Chunk::~Chunk()
{
}

BlockType Chunk::getBlock(int x, int y, int z) const
{
	return m_blocks[x][y][z];
}

ChunkMesh *Chunk::getMesh() const
{
	return m_mesh.get();
}

const glm::ivec2 &Chunk::getPosition() const
{
	return m_position;
}

void Chunk::generateMesh()
{
	m_mesh = std::make_unique<ChunkMesh>(*this);
}
