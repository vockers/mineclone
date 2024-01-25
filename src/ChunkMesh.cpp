#include "ChunkMesh.hpp"

#include "Chunk.hpp"

static const float FRONT_FACE[] = 
{
	// Position
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom left
	1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom right
	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top right
	0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top left
};

static const float BACK_FACE[] = 
{
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  
	1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f
};

static const float LEFT_FACE[] = 
{
	0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f
};

static const float RIGHT_FACE[] = 
{
	1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

static const float TOP_FACE[] = {
	0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

static const float BOTTOM_FACE[] = 
{
	0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
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

typedef struct	block_atlas_s
{
	glm::vec2		front;
	glm::vec2		back;
	glm::vec2		left;
	glm::vec2		right;
	glm::vec2		top;
	glm::vec2		bottom;
}				block_atlas_t;

block_atlas_t	g_block_atlas = {glm::vec2(1, 15), glm::vec2(1, 15), glm::vec2(1, 15), glm::vec2(1, 15), glm::vec2(0, 15), glm::vec2(2, 15)};

ChunkMesh::ChunkMesh(Chunk &chunk)
{
		for (int x = 0; x < CHUNK_SIZE_X; x++) 
	{
		for (int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; z++) 
			{
				BlockType block_type = chunk.getBlock(x, y, z);
				block_atlas_t	block_atlas = g_block_atlas;

				if (block_type == BlockType::Air)
					continue;
				
				// Front face
				if (z == CHUNK_SIZE_Z - 1 || chunk.getBlock(x, y, z + 1) == BlockType::Air)
					addFace(FRONT_FACE, block_atlas.front, glm::vec3(x, y, z));
				// Back face
				if (z == 0 || chunk.getBlock(x, y, z - 1) == BlockType::Air)
					addFace(BACK_FACE, block_atlas.back, glm::vec3(x, y, z));
				// Right face
				if (x == CHUNK_SIZE_X - 1 || chunk.getBlock(x + 1, y, z) == BlockType::Air)
					addFace(RIGHT_FACE, block_atlas.right, glm::vec3(x, y, z));
				// Left face
				if (x == 0 || chunk.getBlock(x - 1, y, z) == BlockType::Air)
					addFace(LEFT_FACE, block_atlas.left, glm::vec3(x, y, z));	
				// Top face
				if (y  == CHUNK_SIZE_Y - 1 || chunk.getBlock(x, y + 1, z) == BlockType::Air)
					addFace(TOP_FACE, block_atlas.top, glm::vec3(x, y, z));
				// Bottom face
				if (y == 0 || chunk.getBlock(x, y - 1, z) == BlockType::Air)
					addFace(BOTTOM_FACE, block_atlas.bottom, glm::vec3(x, y, z));
			}
		}
	}
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glGenBuffers(1, &m_uv_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(float), m_uvs.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
}

ChunkMesh::~ChunkMesh()
{
}

void ChunkMesh::draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ChunkMesh::addFace(const float *face, glm::vec2 uvs, glm::vec3 pos)
{
	for (int i = 0; i < 24;)
	{
		m_vertices.push_back(face[i] + pos.x);
		m_vertices.push_back(face[i + 1] + pos.y);
		m_vertices.push_back(face[i + 2] + pos.z);
		m_vertices.push_back(face[i + 3]);
		m_vertices.push_back(face[i + 4]);
		m_vertices.push_back(face[i + 5]);
		i += 6;
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