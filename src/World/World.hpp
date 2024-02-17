#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

#include "../Camera.hpp"
#include "Chunk.hpp"
#include "ChunkMesh.hpp"

struct KeyHash
{
	std::size_t operator()(const glm::ivec2& k) const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}
	bool operator() (const glm::ivec2& lhs, const glm::ivec2& rhs) const
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};

using ChunkMap = std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, KeyHash, KeyHash>;

class World
{
public:
	World(Camera& camera);
	~World() = default;

	void update();
	void updateChunks();

	const ChunkMap& getChunks() const;

private:
	ChunkMap m_chunks;

	const int RENDER_DISTANCE = 3;

	Camera& m_camera;

	const float CHUNK_UPDATE_MOVE_THRESHOLD = 20.0f;
	glm::vec3 m_old_position;
};