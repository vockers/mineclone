#pragma once

#include <glm/glm.hpp>

#include "World/Block.hpp"

namespace mc
{
class BlockDatabase
{
  public:
    static BlockDatabase &get();

    const BlockData &getData(BlockID type) const;

  private:
    BlockDatabase();
    ~BlockDatabase() = default;

    BlockData m_data[BLOCK_COUNT];
};
} // namespace mc
