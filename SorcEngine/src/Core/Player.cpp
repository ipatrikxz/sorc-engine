#pragma once

#include "Player.h"
#include "Input.h"
#include "Window/Window.h"

Player::Player()
	:
	location(glm::vec3(0, 1.0f, 0)),
	camera(new Camera(location))
{
}

void Player::Init()
{
}

void Player::Update(const float& dt)
{
	UpdateKeyboardInput(dt);
	UpdateMouseInput();
	//camera->UpdateMouseInput(mouseOffsetX, mouseOffsetY);
}

void Player::UpdateKeyboardInput(const float& dt)
{

	/*
	// ESCAPE
	if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
		_window->SetWindowShouldClose(true);
	}

	// Toggle the mouse cursor visiblity
	if (Input::KeyPressed(GLFW_KEY_O)) {
		glfwGetInputMode(GL::GetWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED ?
			glfwSetInputMode(GL::GetWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL) :
			glfwSetInputMode(GL::GetWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	*/

	// WASD
	if (Input::KeyDown(GLFW_KEY_W)) {
		camera->UpdateKeyboardInput(dt, FORWARD);
	}
	if (Input::KeyDown(GLFW_KEY_S)) { 
		camera->UpdateKeyboardInput(dt, BACKWARD);
	}
	if (Input::KeyDown(GLFW_KEY_A)) {
		camera->UpdateKeyboardInput(dt, LEFT);
	}
	if (Input::KeyDown(GLFW_KEY_D)) {
		camera->UpdateKeyboardInput(dt, RIGHT);
	}

	// ascend
	if (Input::KeyDown(GLFW_KEY_E)) {
		camera->UpdateKeyboardInput(dt, UP);
	}

	// descend
	if (Input::KeyDown(GLFW_KEY_Q)) {
		camera->UpdateKeyboardInput(dt, DOWN);
	}

	// camera Speed
	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT)) {
		camera->SetSpeed(8.0f);
	}
	else if (!Input::KeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		camera->SetSpeed(2.5f);
	}

	// For now update the world location to the camera position
	location = camera->GetPosition();
}

void Player::UpdateMouseInput()
{
	/*
	// If the cursor is in normal mode, we don't need to update mouse input
	if(glfwGetInputMode(GL::GetWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
	{
		return;
	}

	GLFWwindow* window = GL::GetWindowPointer();
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = lastMouseY - mouseY;
	lastMouseX = mouseX;
	lastMouseY = mouseY;
	*/
}
