#include "Chunk.hpp"

#include <iostream>

#include "ChunkMesh.hpp"

Chunk::Chunk(glm::ivec2 position) : 
	m_position(position),
	m_mesh(nullptr)
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		m_blocks[x][y][z] = BlockType::Grass;
	}
}

Chunk::~Chunk()
{
}

BlockType Chunk::getBlock(int x, int y, int z) const
{
	return m_blocks[x][y][z];
}

ChunkMesh* Chunk::getMesh() const
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
