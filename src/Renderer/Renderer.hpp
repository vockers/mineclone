#pragma once

#include <GL/glew.h>

#include "../Window.hpp"
#include "../Camera.hpp"
#include "Shader.hpp"
#include "Cubemap.hpp"

namespace mc
{
	struct ProjectionSettings
	{
		float fov;
		float aspect;
		float near;
		float far;
	};

	class Renderer
	{
	public:
		Renderer(Window &window, Camera &camera);
		~Renderer();

		void renderPrepare();
		void renderSkybox();
		void setViewPort(int width, int height);

		const Window &getWindow() const { return m_window; }
		glm::mat4 getProjectionMatrix() const;
		glm::mat4 getOrthoMatrix() const;

	private:
		Window &m_window;
		Camera &m_camera;

		ProjectionSettings m_projection_settings;
		Cubemap m_skybox;
		Shader m_cubemap_shader;
	};
}