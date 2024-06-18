#include "World/ChunkSection.hpp"

namespace mc
{
BlockID ChunkSection::qGetBlock(int x, int y, int z) const
{
    return m_blocks[z * CHUNK_AREA + y * CHUNK_SIZE + x];
}

BlockID ChunkSection::qGetBlock(const glm::ivec3 &pos) const
{
    return qGetBlock(pos.x, pos.y, pos.z);
}

BlockID ChunkSection::getBlock(int x, int y, int z) const
{
    if (!checkBounds(x, y, z))
        return BlockID::Air;

    return qGetBlock(x, y, z);
}

BlockID ChunkSection::getBlock(const glm::ivec3 &pos) const
{
    return getBlock(pos.x, pos.y, pos.z);
}

void ChunkSection::qSetBlock(int x, int y, int z, BlockID block)
{
    m_blocks[z * CHUNK_AREA + y * CHUNK_SIZE + x] = block;
}

void ChunkSection::setBlock(int x, int y, int z, BlockID block)
{
    if (!checkBounds(x, y, z))
        return;

    qSetBlock(x, y, z, block);
}

bool ChunkSection::checkBounds(int x, int y, int z) const
{
    return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE;
}
}; // namespace mc
