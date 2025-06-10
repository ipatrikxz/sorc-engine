#include "Renderer.h"

#include "Shader.h"
#include "Core/GL.h"
#include "Common.h"
#include "Util.hpp"
#include "Renderer.h"

struct Shaders {
	Shader solidColor;
} _shaders;

namespace Renderer 
{
	GLuint _quadVao = 0;
	Model* _testModel = nullptr;

	void Init()
	{
		glEnable(GL_DEPTH_TEST);	// Enable depth testing for 3D rendering
		glDepthFunc(GL_LESS);		// Set depth function to less than (default)
		glEnable(GL_CULL_FACE);		// Enable face culling
		glCullFace(GL_BACK);		// Cull faces
		glFrontFace(GL_CCW);		// Front faces are counterclockwise (default)

		// Load shaders
		_shaders.solidColor.Load("solidcolor.vert", "solidcolor.frag");
	
		// Load models
		_testModel = new Model("res/models/Cube.obj");

		std::cout << "Renderer initialized.\n";
	}

	void RenderFrame(glm::mat4 CameraView)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(FOV), SORC_ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
		glm::mat4 view = CameraView;

		_shaders.solidColor.Use();
		_shaders.solidColor.SetMat4("projection", projection);
		_shaders.solidColor.SetMat4("view", view);

		DrawQuad();

		// Draw Model
		if (_testModel) {
			Transform modelTransform;
			modelTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
			modelTransform.scale = glm::vec3(1.0f);
			_shaders.solidColor.SetVec3("color", WHITE);
			DrawModel(*_testModel, _shaders.solidColor, modelTransform.to_mat4());
		}

	}

	void DrawModel(Model& model, Shader& shader, glm::mat4 transform)
	{
		glDisable(GL_CULL_FACE);
		shader.Use();
		shader.SetMat4("model", transform);
		model.Draw(shader);
		glEnable(GL_CULL_FACE);
	}

	void DrawQuad()
	{
		Transform largeQuad;
		largeQuad.location = glm::vec3(0.0f, 0.0f, 0.0f);
		largeQuad.rotation.x = SORC_PI * -0.5f;
		largeQuad.scale = glm::vec3(25.0f, 25.0f, 1.0f);

		_shaders.solidColor.SetMat4("model", largeQuad.to_mat4());
		_shaders.solidColor.SetVec3("color", DARK);

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

		// Disable culling for the quad
		glDisable(GL_CULL_FACE);
		glBindVertexArray(_quadVao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// Re-enable culling for other objects
		glEnable(GL_CULL_FACE);
	}

	void Cleanup()
	{
		if (_testModel) {
			delete _testModel;
			_testModel = nullptr;
		}
		glDeleteVertexArrays(1, &_quadVao);
	}
}

