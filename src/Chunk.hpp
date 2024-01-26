#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Block.hpp"

constexpr int CHUNK_SIZE = 32;
constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;	

class ChunkMesh;

class Chunk
{
public:
	Chunk(glm::ivec2 position);
	~Chunk();

	BlockType getBlock(int x, int y, int z) const;

	ChunkMesh* getMesh() const;
	const glm::ivec2& getPosition() const;

	void generateMesh();

private:
	glm::ivec2 m_position;
	BlockType m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	std::unique_ptr<ChunkMesh> m_mesh;
};