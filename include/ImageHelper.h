#ifndef _H_IMAGE_HELPER_
#define _H_IMAGE_HELPER_

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <glad//glad.h>
#include <iostream>

class ImageHelper {

private:
	unsigned int texture = 0;
public:
	ImageHelper(bool flip = true) {
		stbi_set_flip_vertically_on_load(flip);
	}

	void loadTexure(const std::string& path, GLenum format) {



		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		std::string fullpath = "../../" + path;
		unsigned char* data = stbi_load(fullpath.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load data, path: " << fullpath << std::endl;
		}

		stbi_image_free(data);
	}

	unsigned int getTexture() {
		return texture;
	}
};

#endif