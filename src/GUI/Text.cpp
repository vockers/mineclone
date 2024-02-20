#include "Text.hpp"

#include <iostream>

Text::Text() : m_font(nullptr)
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

void Text::setText(const std::string &text, float x, float y, float scale)
{
	if (m_font == nullptr)
		return;

	m_text = text;
    glBindVertexArray(m_vao);

    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
    } vertices[6 * text.length()];

    int c = 0;
    for(size_t i = 0; i < text.length(); i++) 
    {
		Character ch = (*m_font)[text[i]];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

		float uvx_left = ch.uv.x;
		float uvx_right = ch.uv.x + (float)ch.size.x / m_font->getAtlasSize().x;
		float uvy_top = (float)ch.size.y / m_font->getAtlasSize().y;

		vertices[c++] = { xpos,     ypos + h,   uvx_left, 0.0f };
		vertices[c++] = { xpos,     ypos,       uvx_left, uvy_top };
        vertices[c++] = { xpos + w, ypos,       uvx_right, uvy_top };

        vertices[c++] = { xpos,     ypos + h,   uvx_left, 0.0f };
    	vertices[c++] = { xpos + w, ypos,       uvx_right, uvy_top };
        vertices[c++] = { xpos + w, ypos + h,   uvx_right, 0.0f };

		x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Text::render()
{
	if (m_font == nullptr)
		return;

	m_font->getShader().bind();
    glBindTexture(GL_TEXTURE_2D, m_font->getTexture());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6 * m_text.length());
	glBindVertexArray(0);
}
