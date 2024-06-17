#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "World/BlockDatabase.hpp"
#include "World/ChunkMesh.hpp"
#include "World/ChunkSection.hpp"

namespace mc
{
	constexpr int CHUNK_SIZE = 32;
	constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
	constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

	class World;
	class ChunkMap;

	class Chunk
	{
	public:
		Chunk(World& world, ChunkMap& map, glm::ivec2 position);
		~Chunk();

		BlockID getBlock(int x, int y, int z) const;;
		BlockID getBlock(const glm::ivec3& pos) const;
		void setBlock(int x, int y, int z, BlockID block);

		ChunkMesh *getMesh() const { return m_mesh.get(); }
		glm::ivec2 getPosition() const { return m_position; }
		glm::vec3 getWorldPosition() const { return glm::vec3(m_position.x * CHUNK_SIZE, 0, m_position.y * CHUNK_SIZE); }
    int getSectionCount() const { return m_sections.size(); }

		void generateMesh();
		void draw(ChunkMesh::Part part) const;

	private:
		World& m_world;
		ChunkMap& m_map;

		int getTopBlock(int x, int z) const;
		bool checkBounds(int x, int y, int z) const;
		void generateTerrain();
		void generateDecorations();
		void generateTree(int x, int y, int z);
		void addSections(size_t index);
		const ChunkSection& getSection(size_t index) const;
		ChunkSection& getSection(size_t index);

		glm::ivec2 m_position;
		// BlockID m_blocks[CHUNK_VOLUME];
		std::vector<ChunkSection> m_sections;
		int m_top_blocks[CHUNK_AREA];
		std::unique_ptr<ChunkMesh> m_mesh;

		static const int OCEAN_LEVEL = 12;
		static const int MIN_HEIGHT = 2;
		static const int MAX_HEIGHT = 105;
    static const int MOUNTAIN_HEIGHT = 45;
    static const int SNOW_HEIGHT = 60;
	};
};
