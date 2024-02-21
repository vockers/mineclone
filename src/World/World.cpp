#include "World.hpp"

World::World(Camera& camera, Renderer& renderer) : 
	m_camera(camera), m_renderer(renderer)
{
	m_block_texture.loadFromFile("assets/textures/blocks.png");
	m_chunk_shader.loadFromFile("assets/shaders/chunk_vertex.glsl", "assets/shaders/chunk_fragment.glsl");

	m_chunks.reserve(RENDER_DISTANCE * RENDER_DISTANCE * 2);
	m_old_position = m_camera.getPosition();

	updateChunks();

	m_update_thread = std::thread(&World::update, this);
}

const ChunkMap& World::getChunks() const
{
	return m_chunks;
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
	glm::ivec2 cam_chunk_pos = glm::ivec2(
		round(m_camera.getPosition().x / CHUNK_SIZE), 
		round(m_camera.getPosition().z / CHUNK_SIZE));

	for (int y = -RENDER_DISTANCE; y < RENDER_DISTANCE; y++)
	{
		for (int x = -RENDER_DISTANCE; x < RENDER_DISTANCE; x++)
		{
			glm::ivec2 chunk_position = glm::ivec2(cam_chunk_pos.x + x, cam_chunk_pos.y + y);
			if (m_chunks.find(chunk_position) == m_chunks.end())
				m_chunks[chunk_position] = std::make_unique<Chunk>(chunk_position);
		}
	}

	for (auto it = m_chunks.begin(); it != m_chunks.end(); it++)
	{
		if (m_chunks.find(glm::ivec2(it->first.x - 1, it->first.y)) != m_chunks.end())
			it->second->setNeighbour(ChunkNeighbour::Left, m_chunks[glm::ivec2(it->first.x - 1, it->first.y)].get());
		if (m_chunks.find(glm::ivec2(it->first.x + 1, it->first.y)) != m_chunks.end())
			it->second->setNeighbour(ChunkNeighbour::Right, m_chunks[glm::ivec2(it->first.x + 1, it->first.y)].get());
		if (m_chunks.find(glm::ivec2(it->first.x, it->first.y - 1)) != m_chunks.end())
			it->second->setNeighbour(ChunkNeighbour::Top, m_chunks[glm::ivec2(it->first.x, it->first.y - 1)].get());
		if (m_chunks.find(glm::ivec2(it->first.x, it->first.y + 1)) != m_chunks.end())
			it->second->setNeighbour(ChunkNeighbour::Bottom, m_chunks[glm::ivec2(it->first.x, it->first.y + 1)].get());
		if (it->second->getMesh() == nullptr)
		{
			it->second->generateMesh();
		}
	}
}

void World::generateChunks()
{

}

void World::render()
{
	m_block_texture.bind();
	m_chunk_shader.bind();
	m_chunk_shader.setUniform("projection", m_renderer.getProjectionMatrix());
	m_chunk_shader.setUniform("view", m_camera.getViewMatrix());

	// Render solid geometry before transparent geometry
	renderChunks(ChunkMeshPart::Base);
	renderChunks(ChunkMeshPart::Transparent);
}

void World::renderChunks(ChunkMeshPart part)
{
	for (auto it = m_chunks.begin(); it != m_chunks.end(); it++)
	{
		Chunk *chunk = it->second.get();
		if (chunk->getMesh() == nullptr)
			continue;
		if (chunk->getMesh()->isGenerated() == false)
			chunk->getMesh()->generateMesh();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, chunk->getWorldPosition());
		m_chunk_shader.setUniform("model", model);
		chunk->getMesh()->draw(part);
	}
}
