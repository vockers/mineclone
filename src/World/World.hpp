#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <thread>

#include "../Camera.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Texture.hpp"
#include "Chunk.hpp"
#include "ChunkMesh.hpp"

namespace mc
{
	struct ChunkPositionHash
	{
		std::size_t operator()(const glm::ivec2 &k) const
		{
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}
		bool operator()(const glm::ivec2 &lhs, const glm::ivec2 &rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};

	using ChunkMap = std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, ChunkPositionHash, ChunkPositionHash>;
	using ChunksVisitedMap = std::unordered_map<glm::ivec2, bool, ChunkPositionHash, ChunkPositionHash>;

	class World
	{
	public:
		World(Camera &camera, Renderer &renderer);
		~World() = default;

		void update();
		void updateChunks();
		void generateChunks(const glm::ivec2 &start, glm::ivec2 current, int distance);
		void render();

		Block getBlock(const glm::ivec3 &position);
		const ChunkMap &getChunks() const;
		std::thread &getUpdateThread() { return m_update_thread; }
		const Shader& getChunkShader() const { return m_chunk_shader; }

	private:
		void renderChunks(ChunkMeshPart part);

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