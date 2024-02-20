#pragma once

#include <string>

#include "Font.hpp"

class Text
{
public:
    Text();
    ~Text();

    void setFont(Font* font);
    void setText(const std::string& text, float x, float y, float scale);
	void render();

private:
	std::string m_text;
    Font* m_font;

    GLuint m_vao;
    GLuint m_vbo;
};
