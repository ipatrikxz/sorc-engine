#pragma once

#include "../Common.h"
#include "Shader.h"
#include "Model.h"

/*
*	Renderer
*
*	Manages rendering logic, including initializing a shader for drawing, setting up a quad (grid square) vertex array object (VAO),
*	and rendering a frame that displays a grid where the color of each square alternates.
*/
namespace Renderer {
	void Init();
	void DrawQuad();
	void DrawModel(Model& model, Shader& shader, glm::mat4 transform);
	void RenderFrame(glm::mat4 CameraView);
	void Cleanup();
}