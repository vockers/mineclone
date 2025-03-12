#pragma once

#include "Utils/PerlinNoise.hpp"
#include "World/Block.hpp"
#include "World/Chunk.hpp"
#include "World/ChunkMap.hpp"

namespace mc
{
class WorldGenerator
{
  public:
    void generate(ChunkMap &chunks, Chunk &chunk);

    static const unsigned int SEED = 12345U;
    static const int OCEAN_LEVEL = 12;
    static const int MIN_HEIGHT = 2;
    static const int MAX_HEIGHT = 105;
    static const int MOUNTAIN_HEIGHT = 35;
    static const int SNOW_HEIGHT = 64;

  private:
    int getHeight(int x, int z);
    BlockID getBlock(int x, int y, int z, int max_height);
    void generateTerrain(Chunk &chunk);
    void generateDecorations(ChunkMap &chunks, Chunk &chunk);
    void generateTree(ChunkMap &chunks, Chunk &chunk, int x, int y, int z);

    const siv::PerlinNoise::seed_type m_seed = SEED;
    const siv::PerlinNoise m_perlin{m_seed};
};
} // namespace mc
