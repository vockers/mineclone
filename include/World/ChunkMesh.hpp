#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../Renderer/Mesh.hpp"
#include "BlockDatabase.hpp"

namespace mc
{
class Chunk;

class ChunkMesh
{
  public:
    using Vertex = Mesh::Vertex;

    enum class Part { Base, Transparent };

    ChunkMesh(Chunk &chunk);

    void draw(Part part);
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
} // namespace mc
