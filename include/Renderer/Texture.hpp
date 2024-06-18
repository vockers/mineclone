#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

namespace mc
{
class Texture
{
  public:
    Texture();
    ~Texture();

    void loadFromFile(const std::string &path);
    void bind();

  protected:
    void generate();

    GLuint m_id;
    GLenum m_format;
    int m_width, m_height;
    std::vector<unsigned char> m_data;
};
} // namespace mc
