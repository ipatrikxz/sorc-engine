
#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Util.hpp"
#include <string>

Texture::Texture(std::string filepath)
{
	Load(filepath);
}

bool Texture::Load(std::string filepath)
{
	if (!Util::FileExists(filepath)) {
		std::cout << filepath << " does not exist.\n";
		return false;
	}
	return false;
}
