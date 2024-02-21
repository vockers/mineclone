#pragma once

#include <glm/glm.hpp>

enum class BlockType : unsigned char
{
	Air,
	Water,
	Stone,
	Grass,
	Sand,
	Wood,
	Leaves,
	Dirt,
};

constexpr int BLOCK_COUNT = static_cast<int>(BlockType::Dirt) + 1;

struct BlockData
{
	glm::ivec2	front;
	glm::ivec2	back;
	glm::ivec2	left;
	glm::ivec2	right;
	glm::ivec2	top;
	glm::ivec2	bottom;
};

class BlockDatabase
{
public:
	static BlockDatabase& get();

	const BlockData& getData(BlockType type) const;

private:
	BlockDatabase();
	~BlockDatabase() = default;

	BlockData m_data[BLOCK_COUNT];
};