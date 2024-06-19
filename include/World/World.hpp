#pragma once

#include <glm/glm.hpp>
#include <thread>

#include "Camera.hpp"
#include "Chunk.hpp"
#include "ChunkMap.hpp"
#include "ChunkMesh.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Texture.hpp"
#include "World/WorldGenerator.hpp"

namespace mc
{
class World
{
  public:
    World(Camera &camera, Renderer &renderer);
    ~World() = default;

    void update();
    void updateChunks();
    void generateChunks(const glm::ivec2 &start, glm::ivec2 current, int distance);
    void render();

    std::thread &getUpdateThread() { return m_update_thread; }
    const Shader &getChunkShader() const { return m_chunk_shader; }

  private:
    void renderChunks(ChunkMesh::Part part);

    Camera &m_camera;
    Renderer &m_renderer;

    Texture m_block_texture;
    Shader m_chunk_shader;
    ChunkMap m_chunks;
    ChunksVisitedMap m_chunks_visited;
    WorldGenerator m_generator;

    std::thread m_update_thread;

    const int RENDER_DISTANCE = 10;
    const float CHUNK_UPDATE_MOVE_THRESHOLD = 20.0f;
    glm::vec3 m_old_position;
};
} // namespace mc
