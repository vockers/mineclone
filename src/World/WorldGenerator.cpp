#include "World/WorldGenerator.hpp"

#include "Utils/PerlinNoise.hpp"

namespace mc
{
int WorldGenerator::getHeight(int x, int z)
{
    const static siv::PerlinNoise::seed_type seed = SEED;
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

void WorldGenerator::generate(Chunk &chunk)
{
    generateTerrain(chunk);
    generateDecorations(chunk);
}

void WorldGenerator::generateTerrain(Chunk &chunk)
{
    glm::ivec2 chunk_pos = chunk.getWorldPosition();

    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            int max_height = getHeight(x + chunk_pos.x, z + chunk_pos.y);
            chunk.setTopBlock(x, z, max_height);
            int check_height = max_height < OCEAN_LEVEL ? OCEAN_LEVEL : max_height;
            for (int y = 0; y <= check_height; y++) {
                BlockID block = getBlock(x + chunk_pos.x, y, z + chunk_pos.y, max_height);
                chunk.setBlock(x, y, z, block);
            }
        }
    }
}

void WorldGenerator::generateDecorations(Chunk &chunk)
{
    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            int max_height = chunk.getTopBlock(x, z);
            if (max_height > OCEAN_LEVEL + 2 && max_height < MOUNTAIN_HEIGHT) {
                if (rand() % 125 > 123)
                    generateTree(chunk, x, max_height + 1, z);
                else if (rand() % 100 > 90)
                    chunk.setBlock(x, max_height + 1, z, BlockID::TallGrass);
                else if (rand() % 100 > 97) {
                    if (rand() % 3 > 1)
                        chunk.setBlock(x, max_height + 1, z, BlockID::YellowFlower);
                    else
                        chunk.setBlock(x, max_height + 1, z, BlockID::Rose);
                }
            }
        }
    }
}

void WorldGenerator::generateTree(Chunk &chunk, int x, int y, int z)
{
    chunk.setBlock(x, y, z, BlockID::Wood);
    int height = (rand() % 3) + 3;

    for (int i = 0; i < height; i++) {
        chunk.setBlock(x, y + i, z, BlockID::Wood);
    }

    int leave_height = (rand() % 2) + 2;
    for (int xx = (x - 2); xx <= (x + 2); xx++) {
        for (int zz = (z - 2); zz <= (z + 2); zz++) {
            for (int yy = (y + height); yy <= (y + height + 1); yy++) {
                int c = 0;
                c += xx == (x - 2) || xx == (x + 2);
                c += zz == (z - 2) || zz == (z + 2);
                bool corner = c == 2;

                if ((!(xx == x && zz == z) || yy > (y + height)) &&
                    !(corner && yy == (y + height + 1) && rand() % 100 > 40))
                    chunk.setBlock(xx, yy, zz, BlockID::Leaves);
            }
        }
    }

    for (int xx = (x - 1); xx <= (x + 1); xx++) {
        for (int zz = (z - 1); zz <= (z + 1); zz++) {
            for (int yy = (y + height + 2); yy <= (y + height + leave_height); yy++) {
                int c = 0;
                c += xx == (x - 1) || xx == (x + 1);
                c += zz == (z - 1) || zz == (z + 1);
                bool corner = c == 2;

                if (!(corner && yy == (y + height + leave_height) && rand() % 100 > 20))
                    chunk.setBlock(xx, yy, zz, BlockID::Leaves);
            }
        }
    }
}
} // namespace mc
