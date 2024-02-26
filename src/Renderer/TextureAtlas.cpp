#include "TextureAtlas.hpp"

#include <iostream>
#include <filesystem>

#include "../Utils/stb_image.h"

void mc::TextureAtlas::loadFromDirectory(const std::string &path, int width, int height)
{
	m_width = width;
	m_height = height;
	m_format = GL_RGBA;

	m_data.reserve(m_width * m_height * 4);
	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		int img_width, img_height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *img = stbi_load(entry.path().c_str(), &img_width, &img_height, &channels, 4);
		if (!img)
		{
			throw std::runtime_error("Failed to load texture: " + entry.path().string());
		}
		std::cout << "Loaded texture: " << entry.path().string() << " " << channels << std::endl;
		if (channels != 4)
		{
			for (int i = 0; i < img_width * img_height * 3; i += 3)
			{
				m_data.push_back(img[i]);
				m_data.push_back(img[i + 1]);
				m_data.push_back(img[i + 2]);
				m_data.push_back((unsigned char)255);
			}
		}
		else
			m_data.insert(m_data.end(), img, img + img_width * img_height * 4);
		stbi_image_free(img);
	}	
	m_data.resize(m_width * m_height * 4);
	generate();
}