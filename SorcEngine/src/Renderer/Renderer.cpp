#include "Renderer.h"

#include <glm/glm.hpp>

#include "../Core/GL.h"
#include "../Core/Input.h"
#include "../Util.hpp"
#include "../Common.h"

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

/*
*	Shader
*
*	Manages shader compilation, linking, error checking, and uniform setting.
*	It loads vertex and fragment shaders from files,
*	compiles them, links them into a shader program,
*	and stores uniform locations for efficient access.
*/
struct Shader {

	int _ID = -1;
	std::unordered_map<std::string, int> _uniformsLocations;

	int CheckErrors(unsigned int shader, std::string type) 
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") 
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) 
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "Shader compilation error: " << type << "\n" << infoLog << "\n";
			}
		}
		else 
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) 
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "Shader linking error: " << type << "\n" << infoLog << "\n";
			}
		}
		return success;
	}

	void Load(std::string vertexPath, std::string fragmentPath) 
	{
		std::string vertexSource = Util::ReadTextFromFile("res/shaders/" + vertexPath);
		std::string fragmentSource = Util::ReadTextFromFile("res/shaders/" + fragmentPath);
		const char* vShaderCode = vertexSource.c_str();
		const char* fShaderCode = fragmentSource.c_str();
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckErrors(vertex, "VERTEX");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		int tempID = glCreateProgram();
		glAttachShader(tempID, vertex);
		glAttachShader(tempID, fragment);
		glLinkProgram(tempID);
		if (CheckErrors(tempID, "PROGRAM")) 
		{
			_uniformsLocations.clear();
			_ID = tempID;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Bind() 
	{
		glUseProgram(_ID);
	}

	void SetMat4(const std::string& name, glm::mat4 value) 
	{
		if (_uniformsLocations.find(name) == _uniformsLocations.end()) {
			_uniformsLocations[name] = glGetUniformLocation(_ID, name.c_str());
		}
		glUniformMatrix4fv(_uniformsLocations[name], 1, GL_FALSE, &value[0][0]);
	}

	void SetVec3(const std::string& name, const glm::vec3& value) 
	{
		if (_uniformsLocations.find(name) == _uniformsLocations.end()) 
		{
			_uniformsLocations[name] = glGetUniformLocation(_ID, name.c_str());
		}
		glUniform3fv(_uniformsLocations[name], 1, &value[0]);
	}
};

namespace Renderer 
{
	Shader _solidColorshader;
	GLuint _quadVao = 0;
}

void Renderer::Init()
{
	_solidColorshader.Load("solidcolor.vert", "solidcolor.frag");
}

void Renderer::DrawQuad()
{
	if (_quadVao == 0) {
		std::vector<Vertex> vertices;
		Vertex vert0 = { glm::vec3(-0.5f,  0.5f, 0.0f) };
		Vertex vert1 = { glm::vec3(0.5f,  0.5f, 0.0f) };
		Vertex vert2 = { glm::vec3(0.5f, -0.5f, 0.0f) };
		Vertex vert3 = { glm::vec3(-0.5f, -0.5f, 0.0f) };
		vertices.push_back(vert0);
		vertices.push_back(vert1);
		vertices.push_back(vert2);
		vertices.push_back(vert3);
		std::vector<unsigned int> indices = { 2, 1, 0, 0, 3, 2 };
		unsigned int VBO;
		unsigned int EBO;
		glGenVertexArrays(1, &_quadVao);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(_quadVao);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glBindVertexArray(_quadVao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderFrame(glm::mat4 CameraView)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(1.0f, 1920.0f / 1080.0f, NEAR_PLANE, FAR_PLANE);
	glm::mat4 view = CameraView;

	_solidColorshader.Bind();
	_solidColorshader.SetMat4("projection", projection);
	_solidColorshader.SetMat4("view", view);

	bool lightSquare = true;

	// grid floor
	for (int x = 0; x < 8; x++) {
		for (int z = 0; z < 8; z++) {

			Transform gridSquare;
			gridSquare.position = glm::vec3(x, 0, z);
			gridSquare.rotation.x = HELL_PI * -0.5f;

			_solidColorshader.SetMat4("model", gridSquare.to_mat4());

			if (lightSquare) {
				_solidColorshader.SetVec3("color", LIGHT_SQUARE);
			}
			else {
				_solidColorshader.SetVec3("color", DARK_SQUARE);
			}
			DrawQuad();
			lightSquare = !lightSquare;
		}
		lightSquare = !lightSquare;
	}

	// Hotload shader
	if (Input::KeyPressed(GLFW_KEY_H)) {
		_solidColorshader.Load("solidcolor.vert", "solidcolor.frag");
	}
}