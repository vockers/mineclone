#pragma once

#include <GL/glew.h>
#include <string>

namespace mc
{
class Cubemap
{
  public:
    Cubemap() = default;
    ~Cubemap();

    void generate(const std::string &top, const std::string &bottom, const std::string &left,
                  const std::string &right, const std::string &front, const std::string &back);
    void draw();

  private:
    void loadSide(GLenum side, const std::string &path);

    GLuint m_id;
    GLuint m_vao;
    GLuint m_vbo;
};
} // namespace mc
