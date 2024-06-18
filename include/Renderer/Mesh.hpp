#pragma once

#include <GL/glew.h>
#include <vector>

namespace mc
{
class Mesh
{
  public:
    using Vertex = uint64_t;

    ~Mesh();

    void addVertex(Vertex vertex);
    void insertVertices(const std::vector<Vertex> &vertices);
    void generate();
    void draw();

  private:
    GLuint m_vao, m_vbo;
    std::vector<Vertex> m_vertices;
    unsigned int m_vertex_count;
};
}; // namespace mc
