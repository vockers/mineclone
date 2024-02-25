#pragma once

#include <glm/glm.hpp>

namespace mc
{
	enum class BlockType : int
	{
		Solid,
		Liquid,
		Flora,
	};

	enum class BlockMeshType : int
	{
		Default,
		Liquid,
		Sprite,
	};

	struct BlockAtlas
	{
		glm::ivec2 front;
		glm::ivec2 back;
		glm::ivec2 left;
		glm::ivec2 right;
		glm::ivec2 top;
		glm::ivec2 bottom;
	};

	enum class Block : unsigned char
	{
		Air,
		Water,
		Stone,
		Grass,
		Sand,
		Wood,
		Leaves,
		TallGrass,
		Dirt,
	};

	constexpr int BLOCK_COUNT = static_cast<int>(Block::Dirt) + 1;

	struct BlockData
	{
		BlockAtlas atlas;
		BlockType type;
		BlockMeshType meshType;
	};

	class BlockDatabase
	{
	public:
		static BlockDatabase &get();

		const BlockData &getData(Block type) const;

	private:
		BlockDatabase();
		~BlockDatabase() = default;

		BlockData m_data[BLOCK_COUNT];
	};
}