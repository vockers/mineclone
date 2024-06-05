#pragma once

#include <glm/glm.hpp>
#include <thread>

#include "../Camera.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/TextureAtlas.hpp"
#include "Chunk.hpp"
#include "ChunkMesh.hpp"
#include "ChunkMap.hpp"

namespace mc
{
	class World
	{
	public:
		World(Camera &camera, Renderer &renderer);
		~World() = default;

		void update();
		void updateChunks(); void generateChunks(const glm::ivec2 &start, glm::ivec2 current, int distance);
		void render();

		BlockID getBlock(const glm::ivec3 &position);
		std::thread &getUpdateThread() { return m_update_thread; }
		const Shader& getChunkShader() const { return m_chunk_shader; }

		static const unsigned int SEED = 12345U;

	private:
		void renderChunks(ChunkMesh::Part part);

		Camera &m_camera;
		Renderer &m_renderer;

		Texture m_block_texture;
		Shader m_chunk_shader;
		ChunkMap m_chunks;
		ChunksVisitedMap m_chunks_visited;

		std::thread m_update_thread;

		const int RENDER_DISTANCE = 10;
		const float CHUNK_UPDATE_MOVE_THRESHOLD = 20.0f;
		glm::vec3 m_old_position;
	};
}
