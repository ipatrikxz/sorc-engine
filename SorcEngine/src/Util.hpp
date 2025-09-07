#pragma once

#include <iostream>	
#include <fstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fileUtil {

	inline std::string ReadTextFromFile(std::string path) {
		std::ifstream file(path);
		std::string str;
		std::string line;
		while (std::getline(file, line)) {
			str += line + "\n";
		}
		return str;
	}

	inline bool FileExists(const std::string name) {
		struct stat buffer;
		return (stat(name.data(), &buffer) == 0);
	}
}

/*
* sVertex is a structure that represents a vertex in 3D space.
* vec3 position
* vec3 normal
* vec2 uv
*/
struct Vertex {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	glm::vec2 uv = glm::vec2(0);
};

/*
* Transform structure holds transformation data for an object in 3D space.
* vec3 location
* vec3 rotation (in radians)
* vec3 scale
* mat4 to_mat4() function converts the transformation data into a 4x4 matrix.
*/
struct Transform {
	glm::vec3 location = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 to_mat4() const {
		glm::mat4 m = glm::translate(glm::mat4(1), location);
		m *= glm::mat4_cast(glm::quat(rotation));
		m = glm::scale(m, scale);
		return m;
	};
};

/*
* Material structure to hold material properties.
* vec3 color, 
* float roughness,
* float metallic, 
* float ambient occlusion
*/
struct Material {
	glm::vec3 color = { 1.0f, 0.0f, 0.0f };
	float roughness = 0.5f;
	float metallic = 0.5f;
	float ambient = 1.0f;

	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 shininess;
};

/*
* directional light structure.
* vec3 direction
* vec3 ambient
* vec3 diffuse
* vec3 specular
*/
struct DirLight {
	glm::vec3 direction = glm::vec3(0, -1, 0);
	glm::vec3 ambient = glm::vec3(1);
	glm::vec3 diffuse = glm::vec3(0);
	glm::vec3 specular = glm::vec3(0);
};