#include "texture.h"

#include <iostream>
#include <string>
#include <glad/glad.h>

#include "stb_image.h"


Texture::Texture(const std::string& path)
{
	this->ID = Texture::load(path);
}

void Texture::Bind(unsigned short pos) const
{
	glActiveTexture(GL_TEXTURE0 + pos);
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

unsigned int Texture::load(const std::string& path)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	unsigned int texture;
	if (data) {
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			nrChannels == 4 ? GL_RGBA : GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 0;
	}
}
