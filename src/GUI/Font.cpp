#include "Font.hpp"

#include <iostream>
#include <algorithm>

Font::Font() : atlas_width(0), m_shader(nullptr)
{
}

Font::~Font()
{
}

void Font::load(FT_Library *ft, const Shader* shader, const char *fontPath, unsigned int fontSize)
{
    FT_Face face;
    if (FT_New_Face(*ft, fontPath, 0, &face))
        throw std::runtime_error("Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    FT_GlyphSlot g = face->glyph;
    unsigned int w = 0;
    unsigned int h = 0;
    for(int i = 32; i < 128; i++)
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            fprintf(stderr, "Loading character %c failed!\n", i);
            continue;
        }

        w += g->bitmap.width;
        h = std::max(h, g->bitmap.rows);
    }
    atlas_width = w;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

    int xoffset = 0;
    for(int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER))
            continue;

        glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, 0, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        chars[i].ax = g->advance.x >> 6;
        chars[i].ay = g->advance.y >> 6;

        chars[i].bw = g->bitmap.width;
        chars[i].bh = g->bitmap.rows;

        chars[i].bl = g->bitmap_left;
        chars[i].bt = g->bitmap_top;

        chars[i].tx = (float)xoffset / w;

        xoffset += g->bitmap.width;
    }
    m_shader = shader;
}
