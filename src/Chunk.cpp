#include "Chunk.hpp"

#include <iostream>

#include "ChunkMesh.hpp"

Chunk::Chunk(glm::ivec2 position) : m_position(position)
{
	for (int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				m_blocks[x][y][z] = BlockType::Grass;
			}
		}
	}
	m_mesh = new ChunkMesh(*this);
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
	return m_mesh;
}
