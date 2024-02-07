#pragma once

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> // Includes the standard I/O stream library. Used for input and output operations, e.g., cout, cin.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>

#include <fstream> // Includes the file stream library. Used for file input and output operations, e.g., ifstream, ofstream.
#include <sstream> // Includes the string stream library. Allows the use of string stream objects, e.g., stringstream, which can be used for parsing and formatting strings.
#include <string> // Includes the standard string library. Provides the std::string class and functions for string manipulation.
#include <vector> // Includes the standard vector library. Provides the std::vector template class, a dynamic array that can resize itself automatically.
#include <unordered_map> // Includes the standard unordered map library. Provides the std::unordered_map template class, a hash table that stores key-value pairs.

#define NEAR_PLANE 0.005f
#define FAR_PLANE 50.0f
#define HELL_PI 3.141592653589793f
#define DARK_SQUARE glm::vec3(0.039f,0.38f,0.286f)
#define LIGHT_SQUARE glm::vec3(0.95703125f, 0.8984375f, 0.74609375f)

/*
*	Vertex
*
*	Defines a vertex's properties, including position, normal, and texture coordinates.
*/
struct Vertex {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	glm::vec2 uv = glm::vec2(0);
};

/*
*	Transform
*
*	Represents a 3D transformation with position, rotation, and scale,
*	converted these properties into a transformation matrix.
*/
struct Transform {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	glm::mat4 to_mat4() {
		glm::mat4 m = glm::translate(glm::mat4(1), position);
		m *= glm::mat4_cast(glm::quat(rotation));
		m = glm::scale(m, scale);
		return m;
	};
};