#pragma once

#include "World/Block.hpp"
#include "World/Chunk.hpp"

namespace mc
{
class WorldGenerator
{
  public:
    void generate(Chunk &chunk);

    static const unsigned int SEED = 12345U;
    static const int OCEAN_LEVEL = 12;
    static const int MIN_HEIGHT = 2;
    static const int MAX_HEIGHT = 105;
    static const int MOUNTAIN_HEIGHT = 45;
    static const int SNOW_HEIGHT = 64;

  private:
    int getHeight(int x, int z);
    BlockID getBlock(int x, int y, int z, int max_height);
    void generateTerrain(Chunk &chunk);
    void generateDecorations(Chunk &chunk);
    void generateTree(Chunk &chunk, int x, int y, int z);
};
} // namespace mc
