#include "Mesh.hpp"

namespace mc
{
    Mesh::~Mesh()
    {
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
    }

    void Mesh::addVertex(Vertex vertex)
    {
        m_vertices.push_back(vertex);
    }

    void Mesh::insertVertices(const std::vector<Vertex>& vertices)
    {
        m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
    }

    void Mesh::generate()
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

        m_vertex_count = m_vertices.size();

        m_vertices.clear();
    }

    void Mesh::draw()
    {
        glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
    }
};