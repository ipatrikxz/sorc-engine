
#include "SceneViewport.h"

#include "Renderer/Renderer.h"
#include "Core/Camera.h"
#include "Core/Input.h"


void SceneRenderer::render()
{
	UpdateDeltaTime();
	Input::Update(windowRef);
    SceneRenderer::HandleInput();
	Renderer::RenderFrame(mCamera->GetViewMatrix());
}

void SceneRenderer::HandleInput()
{
	if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
		glfwTerminate();
	}

	// Toggle the mouse cursor visiblity
	if (Input::KeyPressed(GLFW_KEY_O)) {
		glfwGetInputMode(windowRef, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ?
			glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_NORMAL) :
			glfwSetInputMode(windowRef, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	// WASD
	if (Input::KeyDown(GLFW_KEY_W)) {
		mCamera->UpdateKeyboardInput(deltaTime, FORWARD);
	}
	if (Input::KeyDown(GLFW_KEY_S)) {
		mCamera->UpdateKeyboardInput(deltaTime, BACKWARD);
	}
	if (Input::KeyDown(GLFW_KEY_A)) {
		mCamera->UpdateKeyboardInput(deltaTime, LEFT);
	}
	if (Input::KeyDown(GLFW_KEY_D)) {
		mCamera->UpdateKeyboardInput(deltaTime, RIGHT);
	}

	// camera Speed
	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT)) {
		mCamera->SetSpeed(8.0f);
	}
	else if (!Input::KeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		mCamera->SetSpeed(2.5f);
	}

	// ascend
	if (Input::KeyDown(GLFW_KEY_E)) {
		mCamera->UpdateKeyboardInput(deltaTime, UP);
	}

	// descend
	if (Input::KeyDown(GLFW_KEY_Q)) {
		mCamera->UpdateKeyboardInput(deltaTime, DOWN);
	}

	// Update mouse input
	double mouseX, mouseY;
	glfwGetCursorPos(windowRef, &mouseX, &mouseY);
	cursorPos = Input::UpdateCursorPos(cursorPos, mouseX, mouseY);
	mCamera->UpdateMouseInput(cursorPos.mouseOffsetX, cursorPos.mouseOffsetY);
	
}

void SceneRenderer::load_model(const std::string& filepath)
{
}

void SceneRenderer::resize(int32_t width, int32_t height)
{
}
