#pragma once

#include "GUI/Font.hpp"
#include "GUI/GUI.hpp"
#include "GUI/Text.hpp"

namespace mc
{
class HUD
{
  public:
    HUD(GUI &gui);
    ~HUD() = default;

    void update(float delta_time);
    void render();

  private:
    GUI &m_gui;
    Font m_font;
    Text m_fps_text;

    float m_fps_update_cooldown;
    float m_fps_update_time;
};
} // namespace mc
