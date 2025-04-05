#include "Renderer.h"

#include "Shader.h"
#include "../Core/GL.h"
#include "../Common.h"
#include "../Util.hpp"
#include "../Core/Input.h"


struct Shaders {
	Shader solidColor;
} _shaders;

namespace Renderer 
{
	GLuint _quadVao = 0;
}

void Renderer::Init()
{
	_shaders.solidColor.Load("solidcolor.vert", "solidcolor.frag");
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

	_shaders.solidColor.Use();
	_shaders.solidColor.SetMat4("projection", projection);
	_shaders.solidColor.SetMat4("view", view);

	bool lightSquare = true;

	FTransform gridSquare;
	gridSquare.location = glm::vec3(0, 0, 0);
	gridSquare.rotation.x = SORC_PI * -0.5f;

	_shaders.solidColor.SetMat4("model", gridSquare.to_mat4());
	_shaders.solidColor.SetVec3("color", LIGHT_SQUARE);

	int gridX = 16;
	int gridZ = 16;

	// grid floor
	for (int x = 0; x < gridX; x++) {
		for (int z = 0; z < gridZ; z++) {

			FTransform gridSquare;
			gridSquare.location = glm::vec3(x, 0, z);
			gridSquare.rotation.x = SORC_PI * -0.5f;

			_shaders.solidColor.SetMat4("model", gridSquare.to_mat4());

			if (lightSquare) {
				_shaders.solidColor.SetVec3("color", LIGHT_SQUARE);
			}
			else {
				_shaders.solidColor.SetVec3("color", DARK_SQUARE);
			}
			DrawQuad();
			lightSquare = !lightSquare;
		}
		lightSquare = !lightSquare;
	}

	// Hotload shader
	if (Input::KeyPressed(GLFW_KEY_H)) {
		_shaders.solidColor.Load("solidcolor.vert", "solidcolor.frag");
	}
}