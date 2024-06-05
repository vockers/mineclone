#include "Renderer/Cubemap.hpp"

#include <iostream>

#include "Utils/stb_image.h"

namespace mc
{
	static const float SKYBOX_VERTICES[] =
		{
			// positions
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f};

	Cubemap::~Cubemap()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteTextures(1, &m_id);
	}

	void Cubemap::generate(
		const std::string &top,
		const std::string &bottom,
		const std::string &left,
		const std::string &right,
		const std::string &front,
		const std::string &back)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

		loadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, front);
		loadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, back);
		loadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
		loadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
		loadSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
		loadSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(SKYBOX_VERTICES), &SKYBOX_VERTICES, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void Cubemap::draw()
	{
		glBindVertexArray(m_vao);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void Cubemap::loadSide(GLenum side, const std::string &path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(false);
		unsigned char *img = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!img)
		{
			std::cerr << "Failed to load texture: " << path << std::endl;
			exit(1);
		}

		glTexImage2D(side, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		stbi_image_free(img);
	}
}