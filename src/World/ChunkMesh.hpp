#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Chunk;

using Vertex = uint32_t;

class ChunkMesh
{
public:
	ChunkMesh(Chunk& chunk);
	~ChunkMesh();

	void draw();

private:
	GLuint m_vao;
	GLuint m_vbo, m_uv_vbo;
	GLuint m_ebo;

	std::vector<Vertex> m_vertices;
	std::vector<float> m_uvs;
	std::vector<unsigned int> m_indices;
	unsigned int m_face_count;
	unsigned int m_index_count;

	void addFace(const int *face, glm::vec2 uvs, glm::ivec3 pos);

	static const int POSITION_MASK = 0x1f;
	static const int FACE_BITMASK = 0x7;
};