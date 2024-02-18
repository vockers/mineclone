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
	GLuint m_vbo;

	std::vector<Vertex> m_vertices;
	unsigned int m_vertex_count;

	void addFace(const unsigned int *face, glm::ivec2 uvs, glm::ivec3 pos);
};