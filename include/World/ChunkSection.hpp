#pragma once

#include "World/BlockDatabase.hpp"

constexpr int CHUNK_SIZE = 32;
constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

namespace mc
{
class ChunkSection
{
  public:
    BlockID qGetBlock(int x, int y, int z) const;
    BlockID qGetBlock(const glm::ivec3 &pos) const;
    BlockID getBlock(int x, int y, int z) const;
    ;
    BlockID getBlock(const glm::ivec3 &pos) const;
    void qSetBlock(int x, int y, int z, BlockID block);
    void setBlock(int x, int y, int z, BlockID block);

  private:
    bool checkBounds(int x, int y, int z) const;

    BlockID m_blocks[CHUNK_VOLUME];
};
}; // namespace mc
