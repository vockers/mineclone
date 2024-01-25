#pragma once

#include <glm/glm.hpp>

#include "Block.hpp"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

class ChunkMesh;

class Chunk
{
public:
	Chunk(glm::ivec2 position);
	~Chunk();

	BlockType getBlock(int x, int y, int z) const;

	ChunkMesh* getMesh() const;

private:
	glm::ivec2 m_position;
	BlockType m_blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
	ChunkMesh* m_mesh;
};