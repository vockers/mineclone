#include "Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <GL/glew.h>

#include "Chunk.hpp"
#include "ChunkMesh.hpp"

Chunk* chunk = nullptr;

Renderer::Renderer(sf::Window &window) : m_window(window)
{
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		std::cerr << "Error: glewInit failed: " << glewGetErrorString(glew_status) << std::endl;
		exit(1);
	}

	m_shaders[SHADER_CHUNK].loadFromFile("res/shaders/chunk_vertex.glsl", "res/shaders/chunk_fragment.glsl");

	m_textures[TEXTURE_BLOCKS].loadFromFile("res/textures/blocks.png");

	chunk = new Chunk(glm::ivec2(0, 0));
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);

	m_shaders[SHADER_CHUNK].bind();

    glm::mat4 projection = getProjectionMatrix();
    glm::mat4 view = m_camera.getViewMatrix();


	// mat4_multiply(mvp, projection, view);
	// mat4_identity(model);
	// mat4_translate(model, (vec3_t){(float)chunk->pos.x * CHUNK_SIZE_X, 0.0f, (float)chunk->pos.y * CHUNK_SIZE_Z});
	// mat4_multiply(mvp, mvp, model);
	// glUniformMatrix4fv(glGetUniformLocation(g_renderer.shaders[SHADER_CHUNK], "mvp"), 1, GL_FALSE, *mvp);

	// chunk_mesh_draw(g_chunks[i]->mesh);
	chunk->getMesh()->draw();

	m_window.display();
}

glm::mat4 Renderer::getProjectionMatrix() const
{
	return glm::perspective(
		glm::radians(m_projection_settings.fov),
		m_projection_settings.aspect,
		m_projection_settings.near,
		m_projection_settings.far
	);
}
