#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace mc
{
	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}

	void Shader::loadFromFile(const char *vertex_path, const char *fragment_path)
	{
		std::ifstream vertex_file;
		std::ifstream fragment_file;
		std::string vertex_code;
		std::string fragment_code;

		vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vertex_file.open(vertex_path);
			fragment_file.open(fragment_path);
			std::stringstream vertex_stream;
			std::stringstream fragment_stream;
			vertex_stream << vertex_file.rdbuf();
			fragment_stream << fragment_file.rdbuf();
			vertex_file.close();
			fragment_file.close();
			vertex_code = vertex_stream.str();
			fragment_code = fragment_stream.str();
		}
		catch (std::ifstream::failure &e)
		{
			std::cerr << "Error: Shader::loadFromFile failed: " << e.what() << std::endl;
			exit(1);
		}

		build(vertex_code.c_str(), fragment_code.c_str());
	}

	void Shader::bind() const
	{
		glUseProgram(m_id);
	}

	void Shader::setUniform(const char *name, const glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, &value[0][0]);
	}

	void Shader::setUniform(const char *name, const int value) const
	{
		glUniform1i(glGetUniformLocation(m_id, name), value);
	}

	void Shader::setUniform(const char *name, const glm::vec3 value) const
	{
		glUniform3fv(glGetUniformLocation(m_id, name), 1, &value[0]);
	}

	void Shader::build(const char *vertex_code, const char *fragment_code)
	{
		int success;
		char info_log[1024];

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_code, NULL);
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex_shader, 1024, NULL, info_log);
			throw std::runtime_error("Error: Shader::build failed: vertex shader compilation failed: " + std::string(info_log));
		}

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_code, NULL);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment_shader, 1024, NULL, info_log);
			throw std::runtime_error("Error: Shader::build failed: fragment shader compilation failed: " + std::string(info_log));
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex_shader);
		glAttachShader(m_id, fragment_shader);
		glLinkProgram(m_id);
		glGetShaderiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_id, 1024, NULL, info_log);
			throw std::runtime_error("Error: Shader::build failed: shader program linking failed: " + std::string(info_log));
		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}
}