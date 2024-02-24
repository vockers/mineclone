#include "ChunkMesh.hpp"

#include "Chunk.hpp"

#include <iostream>

// FBLRTB

static const unsigned int FRONT_FACE[] = 
{
	// Position // Normal
	0, 0, 1, 	4,	// Bottom left
	1, 0, 1,	4,	// Bottom right
	1, 1, 1,	4,	// Top right
	0, 0, 1, 	4,	// Bottom left
	1, 1, 1,	4,	// Top right
	0, 1, 1,	4	// Top left
};

static const unsigned int BACK_FACE[] = 
{
	1, 0, 0,	4,
	0, 0, 0,	4,
	0, 1, 0,	4,
	1, 0, 0,	4,
	0, 1, 0,	4,
	1, 1, 0,	4
};

static const unsigned int LEFT_FACE[] = 
{
	0, 0, 0,	3,
	0, 0, 1,	3,
	0, 1, 1,	3,
	0, 0, 0,	3,
	0, 1, 1,	3,
	0, 1, 0,	3
};

static const unsigned int RIGHT_FACE[] = 
{
	1, 0, 1,	3,
	1, 0, 0,	3,
	1, 1, 0,	3,
	1, 0, 1,	3,
	1, 1, 0,	3,
	1, 1, 1,	3
};

static const unsigned int TOP_FACE[] =
{
	0, 1, 1,	5,
	1, 1, 1,	5,
	1, 1, 0,	5,
	0, 1, 1,	5,
	1, 1, 0,	5,
	0, 1, 0,	5
};

static const unsigned int BOTTOM_FACE[] = 
{
	0, 0, 0,	2,
	1, 0, 0,	2,
	1, 0, 1,	2,
	0, 0, 0,	2,
	1, 0, 1,	2,
	0, 0, 1,	2
};

static const unsigned int SPRITE_VERTICES[] = 
{
	1, 0, 0,	5,
	0, 0, 1,	5,
	0, 1, 1,	5,
	1, 0, 0,	5,
	0, 1, 1,	5,
	1, 1, 0,	5,

	0, 0, 0,	5,
	1, 0, 1,	5,
	1, 1, 1,	5,
	0, 0, 0,	5,
	1, 1, 1,	5,
	0, 1, 0,	5
};

static const unsigned int FACE_UVS[] = 
{
	0, 0,
	1, 0,
	1, 1,
	0, 0,
	1, 1,
	0, 1
};

ChunkMesh::ChunkMesh(Chunk &chunk) : m_generated(false)
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

		Block block_type = chunk.getBlock(x, y, z);
		BlockData block_data = BlockDatabase::get().getData(block_type);

		if (block_type == Block::Air)
			continue;
		
		switch (block_data.meshType)
		{
			case BlockMeshType::Sprite:
				addSprite(block_data.atlas.front, glm::ivec3(x, y, z));
				break;
			case BlockMeshType::Default:
			case BlockMeshType::Liquid:
				if (block_type != Block::Water)
				{
					// Front face
					if (canAddFace(block_data, chunk.getBlock(x, y, z + 1)))
						addFace(FRONT_FACE, block_type, block_data.atlas.front, glm::ivec3(x, y, z));
					// Back face
					if (canAddFace(block_data, chunk.getBlock(x, y, z - 1)))
						addFace(BACK_FACE, block_type, block_data.atlas.back, glm::ivec3(x, y, z));
					// Right face
					if (canAddFace(block_data, chunk.getBlock(x + 1, y, z)))
						addFace(RIGHT_FACE, block_type, block_data.atlas.right, glm::ivec3(x, y, z));
					// Left face
					if (canAddFace(block_data, chunk.getBlock(x - 1, y, z)))
						addFace(LEFT_FACE, block_type, block_data.atlas.left, glm::ivec3(x, y, z));	
					// Bottom face
					if (canAddFace(block_data, chunk.getBlock(x, y - 1, z)))
						addFace(BOTTOM_FACE, block_type, block_data.atlas.bottom, glm::ivec3(x, y, z));
				}
				// Top face
				if (canAddFace(block_data, chunk.getBlock(x, y + 1, z)))
					addFace(TOP_FACE, block_type, block_data.atlas.top, glm::ivec3(x, y, z));

				break;
		}
	}
	m_vertices.reserve(m_base_vertices.size() + m_transparent_vertices.size());
	m_vertices.insert(m_vertices.end(), m_base_vertices.begin(), m_base_vertices.end());
	m_vertices.insert(m_vertices.end(), m_transparent_vertices.begin(), m_transparent_vertices.end());
}

ChunkMesh::~ChunkMesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void ChunkMesh::draw(ChunkMeshPart part)
{
	if (!m_generated)
		return;
	glBindVertexArray(m_vao);
	if (part == ChunkMeshPart::Base)
		glDrawArrays(GL_TRIANGLES, 0, m_base_vertex_count);
	else
	{
		glDisable(GL_CULL_FACE);
		glDrawArrays(GL_TRIANGLES, m_base_vertex_count, m_transparent_vertex_count);
		glEnable(GL_CULL_FACE);
	}
	glBindVertexArray(0);
}

void ChunkMesh::generateMesh()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_base_vertex_count = m_base_vertices.size();
	m_transparent_vertex_count = m_transparent_vertices.size();

	m_base_vertices.clear();
	m_transparent_vertices.clear();
	m_vertices.clear();
	
	m_generated = true;
}

bool ChunkMesh::canAddFace(BlockData block_data, Block adjacent_block)
{
	if (adjacent_block == Block::Air)
		return true;

	BlockData adjacent_block_data = BlockDatabase::get().getData(adjacent_block);
	if (adjacent_block_data.type == BlockType::Solid)
		return false;
	else if (block_data.type == BlockType::Liquid && adjacent_block_data.type == BlockType::Liquid)
		return false;
	return true;
}

void ChunkMesh::addFace(const unsigned int *face, Block block_type, glm::ivec2 uvs, glm::ivec3 pos)
{
	for (int i = 0; i < 6; i++)
	{
		// Compress the vertex data into a single 32-bit integer
		Vertex vertex = 0;
		vertex ^= (face[i * 4] + pos.x) << 26;
		vertex ^= (face[i * 4 + 1] + pos.y) << 20;
		vertex ^= (face[i * 4 + 2] + pos.z) << 14;
		vertex ^= face[i * 4 + 3] << 11;
		vertex ^= (FACE_UVS[i * 2] + uvs.x) << 6;
		vertex ^= (FACE_UVS[i * 2 + 1] + uvs.y) << 1;
		if (block_type == Block::Water || block_type == Block::Leaves)
		{
			if (block_type == Block::Water)
				vertex ^= 1;

			m_transparent_vertices.push_back(vertex);
		}
		else
			m_base_vertices.push_back(vertex);
	}
}

void ChunkMesh::addSprite(glm::ivec2 uvs, glm::ivec3 pos)
{
	for (int i = 0; i < 6; i++)
	{
		Vertex vertex = 0;
		vertex ^= (SPRITE_VERTICES[i * 4] + pos.x) << 26;
		vertex ^= (SPRITE_VERTICES[i * 4 + 1] + pos.y) << 20;
		vertex ^= (SPRITE_VERTICES[i * 4 + 2] + pos.z) << 14;
		vertex ^= SPRITE_VERTICES[i * 4 + 3] << 11;
		vertex ^= (FACE_UVS[i * 2] + uvs.x) << 6;
		vertex ^= (FACE_UVS[i * 2 + 1] + uvs.y) << 1;
		m_transparent_vertices.push_back(vertex);
	}

	for (int i = 0; i < 6; i++)
	{
		Vertex vertex = 0;
		vertex ^= (SPRITE_VERTICES[(i + 6) * 4] + pos.x) << 26;
		vertex ^= (SPRITE_VERTICES[(i + 6) * 4 + 1] + pos.y) << 20;
		vertex ^= (SPRITE_VERTICES[(i + 6) * 4 + 2] + pos.z) << 14;
		vertex ^= SPRITE_VERTICES[(i + 6) * 4 + 3] << 11;
		vertex ^= (FACE_UVS[i * 2] + uvs.x) << 6;
		vertex ^= (FACE_UVS[i * 2 + 1] + uvs.y) << 1;
		m_transparent_vertices.push_back(vertex);
	}
}
