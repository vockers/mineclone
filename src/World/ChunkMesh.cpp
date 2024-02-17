#include "ChunkMesh.hpp"

#include "Chunk.hpp"

#include <iostream>

// FBLRTB

static const int FRONT_FACE[] = 
{
	// Position // Normal
	0, 0, 1, 	0, // Bottom left
	1, 0, 1,	0, // Bottom right
	1, 1, 1,	0, // Top right
	0, 1, 1,	0, // Top left
};

static const int BACK_FACE[] = 
{
	1, 0, 0,	1, 
	0, 0, 0,	1,
	0, 1, 0,	1,  
	1, 1, 0,	1
};

static const int LEFT_FACE[] = 
{
	0, 0, 0,	2,
	0, 0, 1,	2,
	0, 1, 1,	2,
	0, 1, 0,	2
};

static const int RIGHT_FACE[] = 
{
	1, 0, 1,	3,
	1, 0, 0,	3,
	1, 1, 0,	3,
	1, 1, 1,	3
};

static const int TOP_FACE[] = {
	0, 1, 1,	4,
	1, 1, 1,	4,
	1, 1, 0,	4,
	0, 1, 0,	4
};

static const int BOTTOM_FACE[] = 
{
	0, 0, 0,	5,
	1, 0, 0,	5,
	1, 0, 1,	5,
	0, 0, 1,	5
};

static const unsigned int FACE_INDICES[] = 
{
	0, 1, 2,
	2, 3, 0,
	4, 5, 6,
	6, 7, 4,
	8, 9, 10,
	10, 11, 8,
	12, 13, 14,
	14, 15, 12,
	16, 17, 18,
	18, 19, 16,
	20, 21, 22,
	22, 23, 20,
};

static const float FACE_UVS[] = {
	0, 0,
	0.0625, 0,
	0.0625, 0.0625,
	0, 0.0625,
};

ChunkMesh::ChunkMesh(Chunk &chunk) : m_face_count(0)
{
	for (int i = 0; i < CHUNK_VOLUME; i++)
	{
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

		BlockType block_type = chunk.getBlock(x, y, z);
		BlockData block_data = BlockDatabase::get().getData(block_type);

		if (block_type == BlockType::Air)
			continue;
		// Front face
		if (z == CHUNK_SIZE - 1 || chunk.getBlock(x, y, z + 1) == BlockType::Air)
			addFace(FRONT_FACE, block_data.front, glm::ivec3(x, y, z));
		// Back face
		if (z == 0 || chunk.getBlock(x, y, z - 1) == BlockType::Air)
			addFace(BACK_FACE, block_data.back, glm::ivec3(x, y, z));
		// Right face
		if (x == CHUNK_SIZE - 1 || chunk.getBlock(x + 1, y, z) == BlockType::Air)
			addFace(RIGHT_FACE, block_data.right, glm::ivec3(x, y, z));
		// Left face
		if (x == 0 || chunk.getBlock(x - 1, y, z) == BlockType::Air)
			addFace(LEFT_FACE, block_data.left, glm::ivec3(x, y, z));	
		// Top face
		if (y  == CHUNK_SIZE - 1 || chunk.getBlock(x, y + 1, z) == BlockType::Air)
			addFace(TOP_FACE, block_data.top, glm::ivec3(x, y, z));
		// Bottom face
		if (y == 0 || chunk.getBlock(x, y - 1, z) == BlockType::Air)
			addFace(BOTTOM_FACE, block_data.bottom, glm::ivec3(x, y, z));
	}
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glGenBuffers(1, &m_uv_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(float), m_uvs.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	m_index_count = m_indices.size();

	m_vertices.clear();
	m_uvs.clear();
	m_indices.clear();
}

ChunkMesh::~ChunkMesh()
{
}

void ChunkMesh::draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ChunkMesh::addFace(const int *face, glm::vec2 uvs, glm::ivec3 pos)
{
	for (int i = 0; i < 4; i++)
	{
		Vertex vertex = 0;
		vertex ^= (face[i * 4] + pos.x) << 26;
		vertex ^= (face[i * 4 + 1] + pos.y) << 20;
		vertex ^= (face[i * 4 + 2] + pos.z) << 14;
		vertex ^= face[i * 4 + 3] << 11;
		m_vertices.push_back(vertex);
	}

	float uv_x = 0.0625 * uvs.x;
	float uv_y = 0.0625 * uvs.y;
	for (int i = 0; i < 8;)
	{
		m_uvs.push_back(FACE_UVS[i] + uv_x);
		m_uvs.push_back(FACE_UVS[i + 1] + uv_y);
		i += 2;
	}

	for (int i = 0; i < 6; i++)
	{
		m_indices.push_back(FACE_INDICES[i] + 4 * m_face_count);
	}
	m_face_count++;
}