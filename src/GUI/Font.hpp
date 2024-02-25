#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "GUI.hpp"

namespace mc
{
	struct Character
	{
		glm::ivec2 size;	  // Size of glyph
		glm::ivec2 bearing;	  // Offset from baseline to left/top of glyph
		glm::vec2 uv;		  // Texture coordinates
		unsigned int advance; // Horizontal offset to advance to next glyph
	};

	class Font
	{
	public:
		Font(GUI &gui);
		~Font();

		void load(const char *fontPath, unsigned int fontSize);

		const Character &operator[](char c) const { return m_chars[(int)c]; }
		glm::ivec2 getAtlasSize() const { return m_atlas_size; }
		GLuint getTexture() const { return m_texture; }
		const Shader &getShader() const { return m_gui.getTextShader(); }

	private:
		GUI &m_gui;

		GLuint m_texture;
		Character m_chars[128];
		glm::ivec2 m_atlas_size;
	};
}