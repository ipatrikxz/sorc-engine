#pragma once

#include "Texture.h"

#include "Util.hpp"
#include "stb_image.h"

Texture::Texture(std::string filepath)
{
	Load(filepath);
}

bool Texture::Load(std::string filepath)
{
    if (!fileUtil::FileExists(filepath)) {
        std::cout << "Texture file does not exist: " << filepath << std::endl;
        return false;
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	// Check if the image was loaded successfully
    if (data) {
        GLenum format = nrChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Texture loaded: " << filepath << " (" << width << "x" << height << ")" << std::endl;
    }
    else {
        std::cout << "Texture loading failed: " << filepath << " (stb_image error: " << stbi_failure_reason() << ")" << std::endl;
        stbi_image_free(data);
        return false;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
    return true;
}
