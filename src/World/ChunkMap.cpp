#include "World/ChunkMap.hpp"

#include <iostream>
#include <memory>

#include "Utils/std_utils.hpp"
#include "World/Block.hpp"

namespace mc
{
ChunkMap::ChunkMap(World &world) : m_world(world) {}

void ChunkMap::addChunk(const glm::ivec2 &position)
{
    if (contains(position))
        return;

    m_chunks[position] = std::make_unique<Chunk>(m_world, *this, position);
}

void ChunkMap::setBlock(Chunk &chunk, int x, int y, int z, BlockID block_id)
{
    if (x < 0 || x >= CHUNK_SIZE || z < 0 || z >= CHUNK_SIZE) {
        glm::ivec2 new_chunk_pos = chunk.getPosition();
        if (x < 0) {
            new_chunk_pos.x -= 1;
            x = CHUNK_SIZE - 1;
        } else if (x >= CHUNK_SIZE) {
            new_chunk_pos.x += 1;
            x = 0;
        }
        if (z < 0) {
            new_chunk_pos.y -= 1;
            z = CHUNK_SIZE - 1;
        } else if (z >= CHUNK_SIZE) {
            new_chunk_pos.y += 1;
            z = 0;
        }
        if (!contains(new_chunk_pos))
            addChunk(new_chunk_pos);
        Chunk &new_chunk = *m_chunks[new_chunk_pos];
        new_chunk.setBlock(x, y, z, block_id);
        return;
    }
    chunk.setBlock(x, y, z, block_id);
}

} // namespace mc
