#pragma once

#include "Texture.hpp"

namespace mc
{
	class TextureAtlas : public Texture
	{
	public:
		void loadFromDirectory(const std::string& path, int width, int height);
	};
}