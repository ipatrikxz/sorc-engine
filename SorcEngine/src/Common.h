#pragma once

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>			// Includes the standard I/O stream library. Used for input and output operations, e.g., cout, cin.
#include <fstream>			// Includes the file stream library. Used for file input and output operations, e.g., ifstream, ofstream.
#include <sstream>			// Includes the string stream library. Allows the use of string stream objects, e.g., stringstream, which can be used for parsing and formatting strings.
#include <string>			// Includes the standard string library. Provides the std::string class and functions for string manipulation.
#include <vector>			// Includes the standard vector library. Provides the std::vector template class, a dynamic array that can resize itself automatically.
#include <unordered_map>	// Includes the standard unordered map library. Provides the std::unordered_map template class, a hash table that stores key-value pairs.
#include <algorithm>		// Includes the standard algorithm library. Provides functions for common algorithms, such as sorting and searching.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>

enum class WindowedMode { WINDOWED, FULLSCREEN };

// Constants
#define APP_NAME			"Sorcery Engine"
#define APP_WINDOW_TITLE	"SorcEngine"
#define APP_VERSION			"0.0.1"

#define SORC_WINDOW_WIDTH	1280
#define SORC_WINDOW_HEIGHT	720
#define SORC_ASPECT_RATIO	(1280.0f / 720.0f)
#define SORC_PI				3.141592653589793f
#define SORC_HALF_PI		1.57079632679f

#define UNDEFINED_STRING	"UNDEFINED_STRING"
#define NEAR_PLANE			0.01f
#define FAR_PLANE			50.0f
#define FOV					50.0f
#define MAX_FOV				120.0f
#define MIN_FOV				45.0f
#define MAX_SPEED			10.0f
#define MIN_SPEED			0.0f

// colors
#define BLACK				glm::vec3(0,0,0)
#define WHITE				glm::vec3(1,1,1)
#define RED					glm::vec3(1,0,0)
#define GREEN				glm::vec3(0,1,0)
#define BLUE				glm::vec3(0,0,1)
#define YELLOW				glm::vec3(1,1,0)
#define PURPLE				glm::vec3(1,0,1)
#define GREY				glm::vec3(0.25f)
#define LIGHT_BLUE			glm::vec3(0,1,1)
#define LIGHT_GREEN			glm::vec3(0.16f, 0.78f, 0.23f)
#define LIGHT_RED			glm::vec3(0.8f, 0.05f, 0.05f)
#define DARK				glm::vec3(0.039f,0.38f,0.286f)
#define LIGHT				glm::vec3(0.95703125f, 0.8984375f, 0.74609375f)


