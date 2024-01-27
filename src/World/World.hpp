#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "../Camera.hpp"
#include "Chunk.hpp"
#include "ChunkMesh.hpp"

using ChunkVector = std::vector<std::unique_ptr<Chunk>>;

class World
{
public:
	World(Camera& camera);
	~World();

	void updateChunks();

	const ChunkVector& getChunks() const;
	Chunk* getChunk(glm::ivec2 position) const;

private:
	ChunkVector m_chunks;

	const int render_distance = 1;

	Camera& m_camera;
};