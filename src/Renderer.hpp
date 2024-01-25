#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Renderer
{
public:
	Renderer(sf::Window& window);
	~Renderer();

	void render();

private:
	sf::Window&	m_window;
	std::vector<std::unique_ptr<sf::Shader>> m_shaders;
	std::vector<std::unique_ptr<sf::Texture>> m_textures;
};