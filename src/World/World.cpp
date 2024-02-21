#include "World.hpp"

World::World(Camera& camera, Renderer& renderer) : 
	m_camera(camera), m_renderer(renderer)
{
	m_block_texture.loadFromFile("assets/textures/blocks.png");
	m_chunk_shader.loadFromFile("assets/shaders/chunk_vertex.glsl", "assets/shaders/chunk_fragment.glsl");

	m_chunks.reserve(RENDER_DISTANCE * RENDER_DISTANCE * 2);
	m_chunks_visited.reserve(RENDER_DISTANCE * RENDER_DISTANCE * 2);
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

	generateChunks(cam_chunk_pos, cam_chunk_pos, RENDER_DISTANCE);
	m_chunks_visited.clear();
}

Chunk* World::generateChunks(const glm::ivec2& start, glm::ivec2 current, int distance)
{
	if (m_chunks_visited.find(current) != m_chunks_visited.end())
		return m_chunks[current].get();
	if (glm::distance(glm::vec2(start), glm::vec2(current)) > distance)
		return nullptr;
	
	m_chunks_visited[current] = true;

	if (m_chunks.find(current) == m_chunks.end())	
	{
		auto chunk = std::make_unique<Chunk>(current);
		chunk.get()->generateMesh();
		m_chunks[current] = std::move(chunk);
	}

	Chunk* chunk = m_chunks[current].get();
	chunk->setNeighbour(ChunkNeighbour::Right, generateChunks(start, glm::ivec2(current.x + 1, current.y), distance));
	chunk->setNeighbour(ChunkNeighbour::Left, generateChunks(start, glm::ivec2(current.x - 1, current.y), distance));
	chunk->setNeighbour(ChunkNeighbour::Top, generateChunks(start, glm::ivec2(current.x, current.y + 1), distance));
	chunk->setNeighbour(ChunkNeighbour::Bottom, generateChunks(start, glm::ivec2(current.x, current.y - 1), distance));

	return chunk;
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
