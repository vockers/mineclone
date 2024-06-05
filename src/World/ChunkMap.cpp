#include "World/ChunkMap.hpp"

#include <memory>

#include "Utils/std_utils.hpp"

namespace mc
{
    ChunkMap::ChunkMap(World &world) : m_world(world)
    {
    }

    void ChunkMap::addChunk(const glm::ivec2 &position)
    {
		if (mapContains(m_chunks, position))
			return;

		auto chunk = std::make_unique<Chunk>(m_world, *this, position);
		chunk.get()->generateMesh();
		m_chunks[position] = std::move(chunk);
	}
}
