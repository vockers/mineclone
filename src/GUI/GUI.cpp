#include "GUI/GUI.hpp"

#include <iostream>

namespace mc
{
GUI::GUI(Renderer &renderer) : m_renderer(renderer)
{
    if (FT_Init_FreeType(&ft))
        throw std::runtime_error("Could not init freetype library");

    m_text_shader.loadFromFile("assets/shaders/text_vertex.glsl",
                               "assets/shaders/text_fragment.glsl");
}

GUI::~GUI() { FT_Done_FreeType(ft); }

void GUI::render()
{
    m_text_shader.bind();
    m_text_shader.setUniform("projection", m_renderer.getOrthoMatrix());
}
} // namespace mc
