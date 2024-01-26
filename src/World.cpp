#include "World.hpp"

#include <iostream>

World::World(Camera& camera) : 
	render_distance(3),
	m_camera(camera)
{
}

World::~World()
{
}

const ChunkVector& World::getChunks() const
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
			if (getChunk(chunk_position) == nullptr)
			{
				m_chunks.push_back(std::make_unique<Chunk>(chunk_position));
			}
		}
	}

	for (size_t i = 0; i < m_chunks.size(); i++)
	{
		if (m_chunks[i]->getMesh() == nullptr)
		{
			m_chunks[i]->generateMesh();
		}
	}
}

Chunk *World::getChunk(glm::ivec2 position) const
{
	for (size_t i = 0; i < m_chunks.size(); i++)
	{
		if (m_chunks[i]->getPosition() == position)
			return m_chunks[i].get();
	}
	return (nullptr);
}
