#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include "utils.h"


Shader::Shader(const std::string& path) {
	unsigned int vertex, fragment;

	vertex = Shader::load(path, GL_VERTEX_SHADER);
	fragment = Shader::load(path, GL_FRAGMENT_SHADER);

	if (!vertex || !fragment) {
		return;
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() const {
	glUseProgram(this->ID);
}

bool Shader::IsLoaded() const {
	return this->ID != 0;
}

unsigned int Shader::load(const std::string& path, unsigned int type) {
	const char* ext;
	switch (type) {
	case GL_VERTEX_SHADER:
		ext = "vert";
		break;
	case GL_FRAGMENT_SHADER:
		ext = "frag";
		break;
	default:
		std::cerr << "Invalid shader type: " << type << std::endl;
		return 0;
	}

	std::string source = readFileContents(path + "/shader." + ext);
	const char* sourceC = source.c_str();
	
	unsigned int shader = glCreateShader(type);
	
	int success;
	
	glShaderSource(shader, 1, &sourceC, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];

		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Failed to compile shader (" << ext << ").\n" << infoLog << std::endl;
		
		return 0;
	}

	return shader;
}
