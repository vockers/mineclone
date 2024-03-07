#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "BlockDatabase.hpp"

namespace mc
{
	constexpr int CHUNK_SIZE = 32;
	constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

	class World;
	class ChunkMap;
	class ChunkMesh;
	enum class ChunkMeshPart;

	class Chunk
	{
	public:
		Chunk(World& world, ChunkMap& map, glm::ivec2 position);
		~Chunk();

		BlockID qGetBlock(const glm::ivec3& pos) const;
		BlockID getBlock(const glm::ivec3& pos) const;

		ChunkMesh *getMesh() const { return m_mesh.get(); }
		glm::ivec2 getPosition() const { return m_position; }
		glm::vec3 getWorldPosition() const { return glm::vec3(m_position.x * CHUNK_SIZE, 0, m_position.y * CHUNK_SIZE); }

		void generateMesh();
		void draw(ChunkMeshPart part) const;

	private:
		World& m_world;
		ChunkMap& m_map;

		int getHeight(int x, int z) const;
		void generateTerrain();
		void generateDecorations();
		void generateTree(int x, int y, int z);

		glm::ivec2 m_position;
		BlockID m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		std::unique_ptr<ChunkMesh> m_mesh;

		static const int OCEAN_LEVEL = 12;
		static const int MIN_HEIGHT = 2;
		static const int MAX_HEIGHT = 32;
	};
};
