#include "BlockDatabase.hpp"

namespace mc
{
	BlockDatabase &BlockDatabase::get()
	{
		static BlockDatabase instance;
		return instance;
	}

	const BlockData &BlockDatabase::getData(BlockID type) const
	{
		return m_data[static_cast<int>(type)];
	}

	BlockDatabase::BlockDatabase()
	{
		m_data[static_cast<int>(BlockID::Water)] = {
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			BlockType::Liquid,
			BlockMeshType::Liquid};
		m_data[static_cast<int>(BlockID::Stone)] = {
			{{3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}, {3, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(BlockID::Grass)] = {
			{{1, 15}, {1, 15}, {1, 15}, {1, 15}, {0, 15}, {2, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(BlockID::Sand)] = {
			{{0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}, {0, 14}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(BlockID::Wood)] = {
			{{2, 14}, {2, 14}, {2, 14}, {2, 14}, {3, 14}, {3, 14}},
			BlockType::Solid,
			BlockMeshType::Default};
		m_data[static_cast<int>(BlockID::Leaves)] = {
			{{4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}, {4, 14}},
			BlockType::Flora,
			BlockMeshType::Default};
		m_data[static_cast<int>(BlockID::TallGrass)] = {
			{{2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}, {2, 12}},
			BlockType::Flora,
			BlockMeshType::Sprite};
		m_data[static_cast<int>(BlockID::Rose)] = {
			{{0, 12}, {0, 12}, {0, 12}, {0, 12}, {0, 12}, {0, 12}},
			BlockType::Flora,
			BlockMeshType::Sprite};
		m_data[static_cast<int>(BlockID::YellowFlower)] = {
			{{1, 12}, {1, 12}, {1, 12}, {1, 12}, {1, 12}, {1, 12}},
			BlockType::Flora,
			BlockMeshType::Sprite};
		m_data[static_cast<int>(BlockID::Dirt)] = {
			{{2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}, {2, 15}},
			BlockType::Solid,
			BlockMeshType::Default};
	}
};