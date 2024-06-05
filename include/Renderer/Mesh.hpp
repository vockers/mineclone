#pragma once

#include <vector>
#include <GL/glew.h>

namespace mc
{
    class Mesh
    {
    public:
	    using Vertex = uint32_t;

        ~Mesh();

        void addVertex(Vertex vertex);
        void insertVertices(const std::vector<Vertex>& vertices);
        void generate();
        void draw();

    private:
        GLuint m_vao, m_vbo;
        std::vector<Vertex> m_vertices;
        unsigned int m_vertex_count;
    };
};