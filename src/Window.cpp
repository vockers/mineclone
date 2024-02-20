#include "Window.hpp"

#include <iostream>

Window::Window(int width, int height, const char *title) : m_closed(false)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed to initialize SDL" << std::endl;
        exit(1);
    }

    // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        std::cerr << "Failed to create window" << std::endl;
        SDL_Quit();
        exit(1);
    }
    
    m_gl_context = SDL_GL_CreateContext(m_window);
}

Window::~Window()
{
    SDL_GL_DeleteContext(m_gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::display()
{
    SDL_GL_SwapWindow(m_window);
}

void Window::close()
{
    m_closed = true;
}

glm::ivec2 Window::getSize() const
{
    int width, height;
    SDL_GetWindowSize(m_window, &width, &height);
    return glm::ivec2(width, height);
}