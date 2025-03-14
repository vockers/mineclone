#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "Chunk.hpp"

namespace mc
{
class World;

struct ChunkPositionHash {
    std::size_t operator()(const glm::ivec2 &k) const
    {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
    }
    bool operator()(const glm::ivec2 &lhs, const glm::ivec2 &rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};
using ChunkHashMap =
    std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, ChunkPositionHash, ChunkPositionHash>;
using ChunksVisitedMap = std::unordered_map<glm::ivec2, bool, ChunkPositionHash, ChunkPositionHash>;

class ChunkMap
{
  public:
    ChunkMap(World &world);

    Chunk &operator[](const glm::ivec2 &position) { return *m_chunks[position]; }

    void addChunk(const glm::ivec2 &position);
    void setBlock(Chunk &chunk, int x, int y, int z, BlockID block_id);

    bool contains(const glm::ivec2 &position) const
    {
        return m_chunks.find(position) != m_chunks.end();
    }
    const ChunkHashMap &getChunks() const { return m_chunks; };

  private:
    World &m_world;

    ChunkHashMap m_chunks;
};
} // namespace mc
