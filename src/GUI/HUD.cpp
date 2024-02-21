#include "HUD.hpp"

#include <iostream>
#include <iomanip>

HUD::HUD(GUI& gui) : m_gui(gui), m_font(m_gui)
{
    m_font.load("assets/fonts/Minecraft.ttf", 14);

    m_fps_text.setFont(&m_font);
	m_fps_update_cooldown = 0.2f;
	m_fps_update_time = 0.0f;
}

void HUD::update(float delta_time)
{
	if (m_fps_update_time <= 0.0f)
	{
		glm::ivec2 window_size = m_gui.getRenderer().getWindow().getSize();
		m_fps_text.setPosition(glm::vec2(25.0f, window_size.y - 25.0f));
    	m_fps_text.setText("FPS: " + std::to_string((int)(1.0f / delta_time)));
		m_fps_update_time = m_fps_update_cooldown;
	}
	m_fps_update_time -= delta_time;
}

void HUD::render()
{
	m_fps_text.render();
}
