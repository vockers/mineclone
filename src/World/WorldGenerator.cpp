#include "World/WorldGenerator.hpp"

#include "Utils/PerlinNoise.hpp"
#include "World/World.hpp"

namespace mc
{
int WorldGenerator::getHeight(int x, int z)
{
    const static siv::PerlinNoise::seed_type seed = World::SEED;
    const static siv::PerlinNoise perlin{seed};

    return glm::clamp((int)(perlin.octave2D_01(x * 0.0045f, z * 0.0045f, 4, 0.7f) * MAX_HEIGHT),
                      MIN_HEIGHT, MAX_HEIGHT);
}

BlockID WorldGenerator::getBlock(int x, int y, int z, int max_height)
{
    BlockID block = BlockID::Air;
    if (y > MOUNTAIN_HEIGHT && y <= max_height) {
        if (y == max_height && y >= SNOW_HEIGHT)
            block = BlockID::Snow;
        else
            block = BlockID::Stone;
    } else if (y < max_height - 3)
        block = BlockID::Stone;
    else if (y < max_height)
        block = BlockID::Dirt;
    else if (y == max_height) {
        if (max_height < OCEAN_LEVEL + 1)
            block = BlockID::Sand;
        else
            block = BlockID::Grass;
    } else if (y >= MIN_HEIGHT && y < OCEAN_LEVEL) {
        block = BlockID::Water;
    }
    return block;
}
} // namespace mc
