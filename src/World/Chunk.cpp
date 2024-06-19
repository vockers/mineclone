#include "World/Chunk.hpp"

#include <glm/glm.hpp>

#include "World/ChunkMap.hpp"
#include "World/ChunkMesh.hpp"
#include "World/World.hpp"
#include "World/world_utils.hpp"

namespace mc
{
Chunk::Chunk(World &world, ChunkMap &map, glm::ivec2 position)
    : m_world(world), m_map(map), m_position(position), m_mesh(nullptr)
{
}

Chunk::~Chunk() {}

BlockID Chunk::getBlock(int x, int y, int z) const
{
    size_t section_index = y / CHUNK_SIZE;
    if (section_index >= m_sections.size())
        return BlockID::Air;
    return getSection(section_index).getBlock(x, y % CHUNK_SIZE, z);
}

BlockID Chunk::getBlock(const glm::ivec3 &pos) const { return getBlock(pos.x, pos.y, pos.z); }

void Chunk::setBlock(int x, int y, int z, BlockID block)
{
    int section_index = y / CHUNK_SIZE;
    addSections(section_index);
    getSection(section_index).setBlock(x, y % CHUNK_SIZE, z, block);
}

void Chunk::generateMesh() { m_mesh = std::make_unique<ChunkMesh>(*this); }

void Chunk::draw(ChunkMesh::Part part) const
{
    if (m_mesh == nullptr)
        return;
    if (m_mesh->isGenerated() == false)
        m_mesh->generateMesh();

    glm::mat4 model = glm::mat4(1.0f);
    glm::ivec2 world_pos = getWorldPosition();
    model = glm::translate(model, glm::vec3(world_pos.x, 0.0f, world_pos.y));
    m_world.getChunkShader().setUniform("model", model);
    m_mesh->draw(part);
}

int Chunk::getTopBlock(int x, int z) const { return m_top_blocks[z * CHUNK_SIZE + x]; }

bool Chunk::checkBounds(int x, int y, int z) const
{
    return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE;
}

void Chunk::addSections(size_t index)
{
    while (index >= m_sections.size())
        m_sections.push_back(ChunkSection());
}

const ChunkSection &Chunk::getSection(size_t index) const { return m_sections[index]; }

ChunkSection &Chunk::getSection(size_t index) { return m_sections[index]; }
} // namespace mc
