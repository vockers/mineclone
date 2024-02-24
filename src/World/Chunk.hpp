#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "BlockDatabase.hpp"

constexpr int CHUNK_SIZE = 32;
constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

enum class ChunkNeighbour : int
{
	Left,
	Right,
	Top,
	Bottom
};

class ChunkMesh;

class Chunk
{
public:
	Chunk(glm::ivec2 position);
	~Chunk();

	Block getBlock(int x, int y, int z) const;

	ChunkMesh* getMesh() const { return m_mesh.get(); }
	glm::ivec2 getPosition() const { return m_position; }
	glm::vec3 getWorldPosition() const { return glm::vec3(m_position.x * CHUNK_SIZE, 0, m_position.y * CHUNK_SIZE); }

	void setNeighbour(ChunkNeighbour neighbour, Chunk *chunk) { m_neighbours[(int)neighbour] = chunk; }

	void generateMesh();

private:
	int getHeight(int x, int z) const;
	void generateTerrain();
	void generateDecorations();
	void generateTree(int x, int y, int z);

	glm::ivec2 m_position;
	Block m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	std::unique_ptr<ChunkMesh> m_mesh;
	Chunk *m_neighbours[4];

	static const int OCEAN_LEVEL = 12;
	static const int MIN_HEIGHT = 2;
	static const int MAX_HEIGHT = 32;
};