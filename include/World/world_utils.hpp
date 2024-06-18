#include <glm/glm.hpp>

namespace mc
{
glm::ivec3 toGlobalBlockPosition(const glm::ivec2 &chunk_position,
                                 const glm::ivec3 &block_position);
glm::ivec3 toLocalVoxelPosition(const glm::ivec3 &global_position);
glm::ivec2 toChunkPosition(const glm::ivec3 &global_position);
} // namespace mc
