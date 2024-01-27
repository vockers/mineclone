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
	m_data[static_cast<int>(BlockType::Stone)] = {{3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}};
	m_data[static_cast<int>(BlockType::Grass)] = {{1, 15}, {1, 15}, {1, 15}, {1, 15}, {0, 15}, {2, 15}};
	m_data[static_cast<int>(BlockType::Dirt)] = {{2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}};
}