#pragma once

#include <ft2build.h>

#include "Font.hpp"
#include "Text.hpp"
#include "../Renderer/Shader.hpp"

class HUD
{
public:
    HUD(const Shader& shader);
    ~HUD() = default;

    void update(float delta_time);
    void render();

private:
    FT_Library ft;
    Font m_font;
    Text m_fps_text;

    const Shader& m_shader;
};