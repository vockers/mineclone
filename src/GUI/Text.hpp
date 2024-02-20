#pragma once

#include <string>

#include "Font.hpp"

class Text
{
public:
    Text();
    ~Text();

    void setFont(Font* font);
    void render(const std::string& text, float x, float y, float scale);

private:
    Font* m_font;

    GLuint m_vao;
    GLuint m_vbo;
};