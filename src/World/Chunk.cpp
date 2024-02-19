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
			int max_height = glm::clamp((int)(perlin.octave2D_01((x + (float)position.x * CHUNK_SIZE) * 0.02f, (z + (float)position.y * CHUNK_SIZE) * 0.02f, 4, 0.35f) * CHUNK_SIZE), MIN_HEIGHT, MAX_HEIGHT);
			int stone_height = max_height - 3;
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				BlockType block = BlockType::Air;
				if (y < stone_height)
					block = BlockType::Stone;
				else if (y < max_height)
					block = BlockType::Dirt;
				else if (y == max_height)
				{
					if (max_height < OCEAN_LEVEL + 1)
						block = BlockType::Sand;
					else
						block = BlockType::Grass;
				}
				else if (y >= MIN_HEIGHT && y < OCEAN_LEVEL)
				{
					block = BlockType::Water;
				}
				else
					block = BlockType::Air;
				m_blocks[x][y][z] = block;
			}
		}
	}
}

Chunk::~Chunk()
{
}

void Chunk::generateMesh()
{
	m_mesh = std::make_unique<ChunkMesh>(*this);
}

void Chunk::generateDecorations()
{
}
