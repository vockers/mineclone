#pragma once

#include <string>

#include "Font.hpp"

namespace mc
{
class Text
{
  public:
    Text();
    ~Text();

    void setFont(Font *font);
    void setPosition(const glm::vec2 &position);
    void setScale(float scale);
    void setText(const std::string &text);
    void render();

  private:
    void updateVBO();

    std::string m_text;
    glm::vec2 m_position;
    float m_scale;
    Font *m_font;

    GLuint m_vao;
    GLuint m_vbo;
};
} // namespace mc
