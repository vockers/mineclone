#include "World.hpp"

#include "world_utils.hpp"
#include "../Utils/std_utils.hpp"

namespace mc
{
	World::World(Camera &camera, Renderer &renderer) : m_camera(camera), m_renderer(renderer), m_chunks(*this)
	{
		m_block_texture.loadFromFile("assets/textures/blocks.png");
		m_chunk_shader.loadFromFile("assets/shaders/chunk_vertex.glsl", "assets/shaders/chunk_fragment.glsl");

		m_chunks_visited.reserve(RENDER_DISTANCE * RENDER_DISTANCE * 2);
		m_old_position = m_camera.getPosition();

		updateChunks();

		m_update_thread = std::thread(&World::update, this);
	}

	BlockID World::getBlock(const glm::ivec3 &position)
	{
		// glm::ivec2 chunk_position = toChunkPosition(position);
		// auto itr = m_chunks.find(chunk_position);
		// if (itr == m_chunks.end()) {
			return BlockID::Air;
		// }
		// return itr->second->qGetBlock(toLocalVoxelPosition(position));
	}

	void World::update()
	{
		while (!m_renderer.getWindow().isClosed())
		{
			// Update chunks if the camera has moved a certain distance
			glm::vec3 distance_moved = m_old_position - m_camera.getPosition();
			if (glm::length(distance_moved) > CHUNK_UPDATE_MOVE_THRESHOLD)
			{
				updateChunks();
				m_old_position = m_camera.getPosition();
			}
		}
	}

	void World::updateChunks()
	{
		// Get the chunk position of the camera
		glm::ivec2 cam_chunk_pos = toChunkPosition(m_camera.getPosition());

		generateChunks(cam_chunk_pos, cam_chunk_pos, RENDER_DISTANCE);
		m_chunks_visited.clear();
	}

	void World::generateChunks(const glm::ivec2 &start, glm::ivec2 current, int distance)
	{
		if (m_chunks_visited.find(current) != m_chunks_visited.end() || 
			glm::distance(glm::vec2(start), glm::vec2(current)) > distance)
			return;

		m_chunks_visited[current] = true;

		m_chunks.addChunk(current);

		generateChunks(start, glm::ivec2(current.x + 1, current.y), distance);
		generateChunks(start, glm::ivec2(current.x - 1, current.y), distance);
		generateChunks(start, glm::ivec2(current.x, current.y + 1), distance);
		generateChunks(start, glm::ivec2(current.x, current.y - 1), distance);
	}

	void World::render()
	{
		m_block_texture.bind();
		m_chunk_shader.bind();
		m_chunk_shader.setUniform("projection", m_renderer.getProjectionMatrix());
		m_chunk_shader.setUniform("view", m_camera.getViewMatrix());

		// Render solid geometry before transparent geometry
		renderChunks(ChunkMesh::Part::Base);
		renderChunks(ChunkMesh::Part::Transparent);
	}

	void World::renderChunks(ChunkMesh::Part part)
	{
		for (auto& [position, chunk] : m_chunks.getChunks())
		{
			chunk->draw(part);
		}
	}
}
