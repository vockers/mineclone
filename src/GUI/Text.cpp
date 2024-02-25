#include "Text.hpp"

#include <iostream>

namespace mc
{
	Text::Text() : m_position(glm::vec2(0.0f, 0.0f)), m_scale(1.0f), m_font(nullptr)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Text::~Text()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Text::setFont(Font *font)
	{
		m_font = font;
	}

	void Text::setPosition(const glm::vec2 &position)
	{
		m_position = position;
		updateVBO();
	}

	void Text::setScale(float scale)
	{
		m_scale = scale;
		updateVBO();
	}

	void Text::setText(const std::string &text)
	{
		m_text = text;
		updateVBO();
	}

	void Text::render()
	{
		if (m_font == nullptr || m_text.empty())
			return;

		m_font->getShader().bind();
		glBindTexture(GL_TEXTURE_2D, m_font->getTexture());
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6 * m_text.length());
		glBindVertexArray(0);
	}

	void Text::updateVBO()
	{
		if (m_font == nullptr || m_text.empty())
			return;

		glBindVertexArray(m_vao);

		struct point
		{
			GLfloat x;
			GLfloat y;
			GLfloat s;
			GLfloat t;
		} vertices[6 * m_text.length()];

		float x = m_position.x;
		int c = 0;
		for (size_t i = 0; i < m_text.length(); i++)
		{
			Character ch = (*m_font)[m_text[i]];

			float xpos = x + ch.bearing.x * m_scale;
			float ypos = m_position.y - (ch.size.y - ch.bearing.y) * m_scale;

			float w = ch.size.x * m_scale;
			float h = ch.size.y * m_scale;

			float uvx_left = ch.uv.x;
			float uvx_right = ch.uv.x + (float)ch.size.x / m_font->getAtlasSize().x;
			float uvy_top = (float)ch.size.y / m_font->getAtlasSize().y;

			vertices[c++] = {xpos, ypos + h, uvx_left, 0.0f};
			vertices[c++] = {xpos, ypos, uvx_left, uvy_top};
			vertices[c++] = {xpos + w, ypos, uvx_right, uvy_top};

			vertices[c++] = {xpos, ypos + h, uvx_left, 0.0f};
			vertices[c++] = {xpos + w, ypos, uvx_right, uvy_top};
			vertices[c++] = {xpos + w, ypos + h, uvx_right, 0.0f};

			x += (ch.advance >> 6) * m_scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}