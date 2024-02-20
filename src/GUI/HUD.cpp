#include "HUD.hpp"

#include <iostream>

HUD::HUD(const Shader& shader) : m_shader(shader)
{
    if(FT_Init_FreeType(&ft))
        throw std::runtime_error("Could not init freetype library");

    m_font.load(&ft, &shader, "res/fonts/Minecraft.ttf", 14);

    m_fps_text.setFont(&m_font);
}

void HUD::update(float delta_time)
{
    // m_fps_text.setString("FPS: " + std::to_string(1.0f / delta_time));
}

void HUD::render()
{
    m_fps_text.render("Hello, world!", 0, 0, 1.0f);
}
