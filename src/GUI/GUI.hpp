#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../Renderer/Renderer.hpp"
#include "../Renderer/Shader.hpp"

namespace mc
{
	class GUI
	{
	public:
		GUI(Renderer &renderer);
		~GUI();

		void render();

		const Renderer &getRenderer() const { return m_renderer; }
		const Shader &getTextShader() const { return m_text_shader; }
		const FT_Library &getFT() const { return ft; }

	private:
		Renderer &m_renderer;

		FT_Library ft;
		Shader m_text_shader;
	};
}