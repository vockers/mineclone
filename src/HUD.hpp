#pragma once

class HUD
{
public:
    HUD();
    ~HUD() = default;

    void update(float delta_time);
    void render();

private:
    // sf::Font m_font;
    // sf::Text m_fps_text;
};