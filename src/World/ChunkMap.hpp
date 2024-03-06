#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

#include "Chunk.hpp"

namespace mc
{
	struct ChunkPositionHash
	{
		std::size_t operator()(const glm::ivec2 &k) const
		{
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}
		bool operator()(const glm::ivec2 &lhs, const glm::ivec2 &rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};
	using ChunkHashMap = std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, ChunkPositionHash, ChunkPositionHash>;
	using ChunksVisitedMap = std::unordered_map<glm::ivec2, bool, ChunkPositionHash, ChunkPositionHash>;

    class ChunkMap
    {
	public:
        ChunkMap();
        
		void addChunk(const glm::ivec2 &position);

		const ChunkHashMap &getChunks() const { return m_chunks; };

    private:
		ChunkHashMap m_chunks;
    };
}
