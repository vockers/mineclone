#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "World/ChunkMesh.hpp"
#include "World/ChunkSection.hpp"

namespace mc
{
constexpr int CHUNK_SIZE = 32;
constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

class World;
class ChunkMap;

class Chunk
{
  public:
    Chunk(World &world, ChunkMap &map, glm::ivec2 position);
    ~Chunk();

    BlockID getBlock(int x, int y, int z) const;
    BlockID getBlock(const glm::ivec3 &pos) const;
    void setBlock(int x, int y, int z, BlockID block);
    void setTopBlock(int x, int z, int height) { m_top_blocks[z * CHUNK_SIZE + x] = height; }

    int getTopBlock(int x, int z) const;
    ChunkMesh *getMesh() const { return m_mesh.get(); }
    glm::ivec2 getPosition() const { return m_position; }
    glm::ivec2 getWorldPosition() const
    {
        return glm::ivec2(m_position.x * CHUNK_SIZE, m_position.y * CHUNK_SIZE);
    }
    int getSectionCount() const { return m_sections.size(); }

    void generateMesh();
    void draw(ChunkMesh::Part part) const;

  private:
    World &m_world;
    ChunkMap &m_map;

    bool checkBounds(int x, int y, int z) const;
    void generateTerrain();
    void generateTree(int x, int y, int z);
    void addSections(size_t index);
    const ChunkSection &getSection(size_t index) const;
    ChunkSection &getSection(size_t index);

    glm::ivec2 m_position;
    std::vector<ChunkSection> m_sections;
    int m_top_blocks[CHUNK_AREA];
    std::unique_ptr<ChunkMesh> m_mesh;
};
} // namespace mc
