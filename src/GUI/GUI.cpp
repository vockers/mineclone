#include "GUI.hpp"

#include <iostream>

GUI::GUI(Renderer& renderer)
	: m_renderer(renderer)
{
	if(FT_Init_FreeType(&ft))
		throw std::runtime_error("Could not init freetype library");

	m_text_shader.loadFromFile("res/shaders/text_vertex.glsl", "res/shaders/text_fragment.glsl");
}

GUI::~GUI()
{
	FT_Done_FreeType(ft);
}

void GUI::render()
{
	m_text_shader.bind();
	m_text_shader.setUniform("projection", m_renderer.getOrthoMatrix());
}
