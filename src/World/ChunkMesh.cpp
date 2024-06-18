#include "World/ChunkMesh.hpp"

#include "World/BlockDatabase.hpp"
#include "World/Chunk.hpp"

// FBLRTB

namespace mc
{
// clang-format off
static const unsigned int FRONT_FACE[] =
{
    // Position // Normal
    0, 0, 1, 4, // Bottom left
    1, 0, 1, 4, // Bottom right
    1, 1, 1, 4, // Top right
    0, 0, 1, 4, // Bottom left
    1, 1, 1, 4, // Top right
    0, 1, 1, 4	// Top left
};

static const unsigned int BACK_FACE[] =
{
    1, 0, 0, 4,
    0, 0, 0, 4,
    0, 1, 0, 4,
    1, 0, 0, 4,
    0, 1, 0, 4,
    1, 1, 0, 4
};

static const unsigned int LEFT_FACE[] =
{
    0, 0, 0, 3,
    0, 0, 1, 3,
    0, 1, 1, 3,
    0, 0, 0, 3,
    0, 1, 1, 3,
    0, 1, 0, 3
};

static const unsigned int RIGHT_FACE[] =
{
    1, 0, 1, 3,
    1, 0, 0, 3,
    1, 1, 0, 3,
    1, 0, 1, 3,
    1, 1, 0, 3,
    1, 1, 1, 3
};

static const unsigned int TOP_FACE[] =
{
    0, 1, 1, 5,
    1, 1, 1, 5,
    1, 1, 0, 5,
    0, 1, 1, 5,
    1, 1, 0, 5,
    0, 1, 0, 5
};

static const unsigned int BOTTOM_FACE[] =
{
    0, 0, 0, 2,
    1, 0, 0, 2,
    1, 0, 1, 2,
    0, 0, 0, 2,
    1, 0, 1, 2,
    0, 0, 1, 2
};

static const unsigned int SPRITE_VERTICES[] =
{
    1, 0, 0, 5,
    0, 0, 1, 5,
    0, 1, 1, 5,
    1, 0, 0, 5,
    0, 1, 1, 5,
    1, 1, 0, 5,

    0, 0, 0, 5,
    1, 0, 1, 5,
    1, 1, 1, 5,
    0, 0, 0, 5,
    1, 1, 1, 5,
    0, 1, 0, 5
};

static const unsigned int FACE_UVS[] =
{
    0, 0,
    1, 0,
    1, 1,
    0, 0,
    1, 1,
    0, 1
};
// clang-format on

ChunkMesh::ChunkMesh(Chunk &chunk) : m_generated(false)
{
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * (CHUNK_SIZE * chunk.getSectionCount()); i++) {
        int x = i % CHUNK_SIZE;
        int y = i / (CHUNK_SIZE * CHUNK_SIZE);
        int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

        BlockID block_type = chunk.getBlock(x, y, z);
        BlockData block_data = BlockDatabase::get().getData(block_type);

        if (block_type == BlockID::Air)
            continue;

        switch (block_data.meshType) {
        case BlockMeshType::Sprite:
            addSprite(block_data.atlas.front, glm::ivec3(x, y, z));
            break;
        case BlockMeshType::Default:
            // Front face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x, y, z + 1))))
                addFace(FRONT_FACE, block_data.type, block_data.atlas.front, glm::ivec3(x, y, z));
            // Back face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x, y, z - 1))))
                addFace(BACK_FACE, block_data.type, block_data.atlas.back, glm::ivec3(x, y, z));
            // Right face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x + 1, y, z))))
                addFace(RIGHT_FACE, block_data.type, block_data.atlas.right, glm::ivec3(x, y, z));
            // Left face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x - 1, y, z))))
                addFace(LEFT_FACE, block_data.type, block_data.atlas.left, glm::ivec3(x, y, z));
            // Bottom face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x, y - 1, z))))
                addFace(BOTTOM_FACE, block_data.type, block_data.atlas.bottom, glm::ivec3(x, y, z));
        case BlockMeshType::Liquid:
            // Top face
            if (canAddFace(block_data, chunk.getBlock(glm::ivec3(x, y + 1, z))))
                addFace(TOP_FACE, block_data.type, block_data.atlas.top, glm::ivec3(x, y, z));

            break;
        }
    }
}

void ChunkMesh::draw(Part part)
{
    if (!m_generated)
        return;

    if (part == Part::Base)
        m_base_mesh.draw();
    else {
        glDisable(GL_CULL_FACE);
        m_transparent_mesh.draw();
        glEnable(GL_CULL_FACE);
    }
}

void ChunkMesh::generateMesh()
{
    m_base_mesh.generate();
    m_transparent_mesh.generate();

    m_generated = true;
}

bool ChunkMesh::canAddFace(BlockData block_data, BlockID adjacent_block)
{
    if (adjacent_block == BlockID::Air)
        return true;
    else if (block_data.type == BlockType::Flora)
        return true;

    BlockData adjacent_block_data = BlockDatabase::get().getData(adjacent_block);
    if (adjacent_block_data.type == BlockType::Solid)
        return false;
    else if (block_data.type == BlockType::Liquid && adjacent_block_data.type == BlockType::Liquid)
        return false;
    return true;
}

void ChunkMesh::addFace(const unsigned int *face, BlockType block_type, glm::ivec2 uvs,
                        glm::ivec3 pos)
{
    for (int i = 0; i < 6; i++) {
        // Compress the vertex data into a single 64-bit integer
        Vertex vertex = 0;
        vertex ^= (face[i * 4] + pos.x) << 26;
        vertex ^= (Vertex)(face[i * 4 + 1] + pos.y) << 52;
        vertex ^= (face[i * 4 + 2] + pos.z) << 14;
        vertex ^= face[i * 4 + 3] << 11;
        vertex ^= (FACE_UVS[i * 2] + uvs.x) << 6;
        vertex ^= (FACE_UVS[i * 2 + 1] + uvs.y) << 1;
        if (block_type == BlockType::Liquid || block_type == BlockType::Flora) {
            if (block_type == BlockType::Liquid)
                vertex ^= 1;

            m_transparent_mesh.addVertex(vertex);
        } else
            m_base_mesh.addVertex(vertex);
    }
}

void ChunkMesh::addSprite(glm::ivec2 uvs, glm::ivec3 pos)
{
    addFace(SPRITE_VERTICES, BlockType::Flora, uvs, pos);
    addFace(&SPRITE_VERTICES[6 * 4], BlockType::Flora, uvs, pos);
}
}; // namespace mc
