#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace mc
{
class Shader
{
  public:
    Shader() = default;
    ~Shader();

    void loadFromFile(const char *vertex_path, const char *fragment_path);
    void bind() const;

    void setUniform(const char *name, const glm::mat4 value) const;
    void setUniform(const char *name, const int value) const;
    void setUniform(const char *name, const glm::vec3 value) const;

  private:
    GLuint m_id;

    void build(const char *vertex_code, const char *fragment_code);
};
} // namespace mc
