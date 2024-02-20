#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../Renderer/Shader.hpp"

struct Character {
    float ax; // advance.x
    float ay; // advance.y
    
    float bw; // bitmap.width;
    float bh; // bitmap.rows;
    
    float bl; // bitmap_left;
    float bt; // bitmap_top;
    
    float tx; // x offset of glyph in texture coordinates
};

class Font
{
public:
    Font();
    ~Font();

    void load(FT_Library* ft, const Shader* shader, const char* fontPath, unsigned int fontSize);

    const Character& operator[](char c) const { return chars[(int)c]; }
    unsigned int getAtlasWidth() const { return atlas_width; }
    GLuint getTexture() const { return texture; }
    const Shader* getShader() const { return m_shader; }

private:
    GLuint texture;
    Character chars[128];
    unsigned int atlas_width;

    const Shader* m_shader;
};