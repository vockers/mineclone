#pragma once

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void display();
    void close();

    bool isClosed() const { return m_closed; }

    SDL_Window* getWindow() const { return m_window; }
    glm::ivec2 getSize() const;

private:
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;
    bool m_closed;
};