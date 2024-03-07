#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "BlockDatabase.hpp"

namespace mc
{
	class Chunk;

	using Vertex = uint32_t;

	enum class ChunkMeshPart
	{
		Base,
		Transparent
	};

	class ChunkMesh
	{
	public:
		ChunkMesh(Chunk &chunk);
		~ChunkMesh();

		void draw(ChunkMeshPart part);
		void generateMesh();

		bool isGenerated() const { return m_generated; }

	private:
		GLuint m_vao;
		GLuint m_vbo;

		std::vector<Vertex> m_vertices;
		std::vector<Vertex> m_base_vertices;
		std::vector<Vertex> m_transparent_vertices;
		unsigned int m_base_vertex_count;
		unsigned int m_transparent_vertex_count;

		bool m_generated;

		bool canAddFace(BlockData block_data, BlockID adjacent_block);
		void addFace(const unsigned int *face, BlockID block_type, glm::ivec2 uvs, glm::ivec3 pos);
		void addSprite(glm::ivec2 uvs, glm::ivec3 pos);
	};
}