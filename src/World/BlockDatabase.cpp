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
	m_data[static_cast<int>(BlockType::Water)] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	m_data[static_cast<int>(BlockType::Stone)] = {{3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}};
	m_data[static_cast<int>(BlockType::Grass)] = {{1, 15}, {1, 15}, {1, 15}, {1, 15}, {0, 15}, {2, 15}};
	m_data[static_cast<int>(BlockType::Sand)] = {{0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}};
	m_data[static_cast<int>(BlockType::Wood)] = {{2, 14}, {2, 14}, {2, 14}, {2, 14}, {3, 14}, {3, 14}};
	m_data[static_cast<int>(BlockType::Leaves)] = {{4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}};
	m_data[static_cast<int>(BlockType::Dirt)] = {{2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}};
}