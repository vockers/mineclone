#include "World.hpp"

#include <iostream>

World::World(Camera& camera) : 
	m_camera(camera)
{
}

const ChunkMap& World::getChunks() const
{
	return m_chunks;
}

void World::updateChunks()
{
	int current_chunk_coord_x = round(m_camera.getPosition().x / CHUNK_SIZE);
	int current_chunk_coord_y = round(m_camera.getPosition().z / CHUNK_SIZE);

	for (int y = -render_distance; y < render_distance; y++)
	{
		for (int x = -render_distance; x < render_distance; x++)
		{
			glm::ivec2 chunk_position = glm::ivec2(current_chunk_coord_x + x, current_chunk_coord_y + y);
			if (m_chunks.find(chunk_position) == m_chunks.end())
				m_chunks[chunk_position] = std::make_unique<Chunk>(chunk_position);
		}
	}

	for (auto it = m_chunks.begin(); it != m_chunks.end(); it++)
	{
		if (it->second->getMesh() == nullptr)
		{
			it->second->generateMesh();
		}
	}
}
