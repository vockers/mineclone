#include "BlockDatabase.hpp"

BlockDatabase &BlockDatabase::get()
{
	static BlockDatabase instance;
	return instance;
}

const BlockData &BlockDatabase::getData(BlockType type) const
{
	return m_data[static_cast<int>(type)];
}

BlockDatabase::BlockDatabase()
{
	m_data[static_cast<int>(BlockType::Water)] = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, BlockMeshType::Liquid};
	m_data[static_cast<int>(BlockType::Stone)] = {{{3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}}, BlockMeshType::Default};
	m_data[static_cast<int>(BlockType::Grass)] = {{{1, 15}, {1, 15}, {1, 15}, {1, 15}, {0, 15}, {2, 15}}, BlockMeshType::Default};
	m_data[static_cast<int>(BlockType::Sand)] = {{{0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}}, BlockMeshType::Default};
	m_data[static_cast<int>(BlockType::Wood)] = {{{2, 14}, {2, 14}, {2, 14}, {2, 14}, {3, 14}, {3, 14}}, BlockMeshType::Default};
	m_data[static_cast<int>(BlockType::Leaves)] = {{{4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}}, BlockMeshType::Default};
	m_data[static_cast<int>(BlockType::TallGrass)] = {{{2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}}, BlockMeshType::Sprite};
	m_data[static_cast<int>(BlockType::Dirt)] = {{{2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}}, BlockMeshType::Default};
}