#include "World/TerrainGenerator.hpp"

#include "Utils/PerlinNoise.hpp"
#include "World/World.hpp"

namespace mc
{
int TerrainGenerator::getHeight(int x, int z)
{
    const static siv::PerlinNoise::seed_type seed = World::SEED;
    const static siv::PerlinNoise perlin{seed};

    return glm::clamp((int)(perlin.octave2D_01(x * 0.0045f,
                                        z * 0.0045f, 4, 0.7f) *
                     MAX_HEIGHT),
               MIN_HEIGHT, MAX_HEIGHT);
}
} // namespace mc
