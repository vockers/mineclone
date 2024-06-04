#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "BlockDatabase.hpp"
#include "../Renderer/Mesh.hpp"

namespace mc
{
	class Chunk;

	enum class ChunkMeshPart
	{
		Base,
		Transparent
	};

	class ChunkMesh
	{
	public:
		using Vertex = Mesh::Vertex;

		ChunkMesh(Chunk &chunk);

		void draw(ChunkMeshPart part);
		void generateMesh();

		bool isGenerated() const { return m_generated; }

	private:
		Mesh m_base_mesh;
		Mesh m_transparent_mesh;

		bool m_generated;

		bool canAddFace(BlockData block_data, BlockID adjacent_block);
		void addFace(const unsigned int *face, BlockType block_type, glm::ivec2 uvs, glm::ivec3 pos);
		void addSprite(glm::ivec2 uvs, glm::ivec3 pos);
	};
}