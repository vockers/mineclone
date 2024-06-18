#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

namespace mc
{
class Window
{
  public:
    Window(int width, int height, const std::string &title);
    ~Window();

    void display();
    void close();

    bool isClosed() const { return m_closed; }

    SDL_Window *getWindow() const { return m_window; }
    glm::ivec2 getSize() const;

  private:
    SDL_Window *m_window;
    SDL_GLContext m_gl_context;
    bool m_closed;
};
} // namespace mc
