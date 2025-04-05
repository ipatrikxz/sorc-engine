#pragma once

#include "Player.h"

#include "Camera.h"
#include "Input.h"
#include "GL.h"

Player::Player()
{
	mouseX = 0;
	mouseY = 0;
	lastMouseX = 0;
	lastMouseY = 0;
	mouseOffsetX = 0;
	mouseOffsetY = 0;

	camera = new Camera();
}

void Player::Update(const float& dt)
{
	Input::Update();
	UpdateKeyboardInput(dt);
	UpdateMouseInput();
	camera->UpdateInput(dt, 0, mouseOffsetX, mouseOffsetY);
}

void Player::UpdateKeyboardInput(const float& dt)
{
	// ESCAPE
	if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
		GL::SetWindowShouldClose(true);
	}

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

	if (Input::KeyDown(GLFW_KEY_E)) {
		camera->UpdateKeyboardInput(dt, UP);
	}

	if (Input::KeyDown(GLFW_KEY_Q)) {
		camera->UpdateKeyboardInput(dt, DOWN);
	}

	// Camera Speed
	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT)) {
		camera->SetSpeed(8.0f);
	}
	else if (!Input::KeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		camera->SetSpeed(2.5f);
	}

}

void Player::UpdateMouseInput()
{
	GLFWwindow* window = GL::GetWindowPointer();
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = lastMouseY - mouseY;
	lastMouseX = mouseX;
	lastMouseY = mouseY;
}

glm::mat4 Player::GetViewMatrix()
{
	return camera->GetViewMatrix();
}