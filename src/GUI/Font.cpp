#include "GUI/Font.hpp"

#include <algorithm>
#include <iostream>

namespace mc
{
Font::Font(GUI &gui) : m_gui(gui) {}

Font::~Font() { glDeleteTextures(1, &m_texture); }

void Font::load(const char *fontPath, unsigned int fontSize)
{
    FT_Face face;
    if (FT_New_Face(m_gui.getFT(), fontPath, 0, &face))
        throw std::runtime_error("Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    unsigned int w = 0;
    unsigned int h = 0;
    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
            continue;

        w += face->glyph->bitmap.width;
        h = std::max(h, face->glyph->bitmap.rows);
    }
    m_atlas_size.x = w;
    m_atlas_size.y = h;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

    int xoffset = 0;
    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
            continue;

        glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, 0, face->glyph->bitmap.width,
                        face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer);

        m_chars[i].size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        m_chars[i].bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        m_chars[i].uv = glm::vec2((float)xoffset / (float)w, 0.0f);
        m_chars[i].advance = static_cast<unsigned int>(face->glyph->advance.x);

        xoffset += face->glyph->bitmap.width;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}
} // namespace mc
