#pragma once

#include "World/Block.hpp"

namespace mc
{
class WorldGenerator
{
  public:
    static int getHeight(int x, int z);
    static BlockID getBlock(int x, int y, int z, int max_height);

    static const int OCEAN_LEVEL = 12;
    static const int MIN_HEIGHT = 2;
    static const int MAX_HEIGHT = 105;
    static const int MOUNTAIN_HEIGHT = 45;
    static const int SNOW_HEIGHT = 60;
};
} // namespace mc
