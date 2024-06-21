#pragma once

#include <glm/glm.hpp>

namespace mc
{
enum class BlockType : int {
    Solid,
    Liquid,
    Flora,
};

enum class BlockMeshType : int {
    Default,
    Liquid,
    Sprite,
};

struct BlockAtlas {
    glm::ivec2 front;
    glm::ivec2 back;
    glm::ivec2 left;
    glm::ivec2 right;
    glm::ivec2 top;
    glm::ivec2 bottom;
};

enum class BlockID : unsigned char {
    Air,
    Water,
    Stone,
    Grass,
    Sand,
    Wood,
    Leaves,
    TallGrass,
    Rose,
    YellowFlower,
    Snow,
    Lava,
    Dirt,
};

constexpr int BLOCK_COUNT = static_cast<int>(BlockID::Dirt) + 1;

struct BlockData {
    BlockAtlas atlas;
    BlockType type;
    BlockMeshType meshType;
};
} // namespace mc
