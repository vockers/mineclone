#include "World/world_utils.hpp"

#include "World/Chunk.hpp"

namespace mc
{
glm::ivec3 toGlobalBlockPosition(const glm::ivec2 &chunk_position, const glm::ivec3 &block_position)
{
    return glm::ivec3(chunk_position.x * CHUNK_SIZE + block_position.x, block_position.y,
                      chunk_position.y * CHUNK_SIZE + block_position.z);
}

glm::ivec3 toLocalVoxelPosition(const glm::ivec3 &position)
{
    return glm::ivec3((CHUNK_SIZE + (position.x % CHUNK_SIZE)) % CHUNK_SIZE, position.y,
                      (CHUNK_SIZE + (position.z % CHUNK_SIZE)) % CHUNK_SIZE);
}

glm::ivec2 toChunkPosition(const glm::ivec3 &position)
{
    return glm::ivec2(position.x / CHUNK_SIZE, position.z / CHUNK_SIZE);
}
} // namespace mc
