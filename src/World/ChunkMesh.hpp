#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Chunk;

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

	std::vector<float> m_vertices;
	std::vector<float> m_uvs;
	std::vector<unsigned int> m_indices;
	unsigned int m_face_count;
	unsigned int m_index_count;

	void addFace(const float *face, glm::vec2 uvs, glm::vec3 pos);
};