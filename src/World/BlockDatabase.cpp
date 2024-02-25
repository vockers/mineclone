#include "BlockDatabase.hpp"

namespace mc
{
	BlockDatabase &BlockDatabase::get()
	{
		static BlockDatabase instance;
		return instance;
	}

	const BlockData &BlockDatabase::getData(Block type) const
	{
		return m_data[static_cast<int>(type)];
	}

	BlockDatabase::BlockDatabase()
	{
		m_data[static_cast<int>(Block::Water)] = {
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			BlockType::Liquid,
			BlockMeshType::Liquid};
		m_data[static_cast<int>(Block::Stone)] = {
			{{3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(Block::Grass)] = {
			{{1, 15}, {1, 15}, {1, 15}, {1, 15}, {0, 15}, {2, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(Block::Sand)] = {
			{{0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(Block::Wood)] = {
			{{2, 14}, {2, 14}, {2, 14}, {2, 14}, {3, 14}, {3, 14}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(Block::Leaves)] = {
			{{4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(Block::TallGrass)] = {
			{{2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}},
			BlockType::Flora,
			BlockMeshType::Sprite};
		m_data[static_cast<int>(Block::Dirt)] = {
			{{2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
	}
};