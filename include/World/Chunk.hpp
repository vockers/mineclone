#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "BlockDatabase.hpp"
#include "ChunkMesh.hpp"

namespace mc
{
	constexpr int CHUNK_SIZE = 32;
	constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

	class World;
	class ChunkMap;

	class Chunk
	{
	public:
		Chunk(World& world, ChunkMap& map, glm::ivec2 position);
		~Chunk();

		BlockID qGetBlock(int x, int y, int z) const;
		BlockID qGetBlock(const glm::ivec3& pos) const;
		BlockID getBlock(int x, int y, int z) const;;
		BlockID getBlock(const glm::ivec3& pos) const;
		void qSetBlock(int x, int y, int z, BlockID block);

		ChunkMesh *getMesh() const { return m_mesh.get(); }
		glm::ivec2 getPosition() const { return m_position; }
		glm::vec3 getWorldPosition() const { return glm::vec3(m_position.x * CHUNK_SIZE, 0, m_position.y * CHUNK_SIZE); }

		void generateMesh();
		void draw(ChunkMesh::Part part) const;

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
