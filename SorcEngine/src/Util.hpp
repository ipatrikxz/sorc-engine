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
* It contains position, normal, and UV coordinates.
* The position is a 3D vector representing the vertex's location in space,
* the normal is a 3D vector representing the vertex's normal direction, and
* the UV is a 2D vector representing the texture coordinates of the vertex.
*/
struct sVertex {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	glm::vec2 uv = glm::vec2(0);
};


/*
* sTransform is a structure that holds transformation data for an object in 3D space.
* It includes location, rotation, and scale properties, and provides a method to convert these properties into a 4x4 transformation matrix.
* The transformation matrix is constructed by first translating the object to its location, then applying rotation using a quaternion derived from the rotation vector, and finally scaling the object.
*/
struct sTransform {
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
* sMaterial is a simple structure to hold material properties.
* It contains color, roughness, metallic, and ambient occlusion properties.
*/
struct sMaterial {
	glm::vec3 color = { 1.0f, 0.0f, 0.0f };
	float roughness = 0.5f;
	float metallic = 0.5f;
	float ao = 1.0f; // ambient occlusion
};