#pragma once

#include "Camera.h"

class Window;

class Camera;

class Player {

private:

	Camera* camera;

	glm::vec3 location;

	/*
	// Input
	double mouseX;
	double mouseY;
	double lastMouseX;
	double lastMouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	*/

public:

	Player();
	~Player() {};

	void Init();
	void Update(const float& dt);
	void UpdateKeyboardInput(const float& dt);
	void UpdateMouseInput();

	glm::vec3 GetWorldLocation() const { return location; }
	glm::mat4 GetViewMatrix() const { return camera->GetViewMatrix(); }

};