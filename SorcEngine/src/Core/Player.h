#pragma once

#include <glm/glm.hpp>

class Camera;

// Enums
enum EDirection {
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 3,
	RIGHT = 4,
	UP = 5,
	DOWN = 6
};

class Player {

private:
	double mouseX;
	double mouseY;
	double lastMouseX;
	double lastMouseY;
	double mouseOffsetX;
	double mouseOffsetY;

	Camera* camera;

public:

	Player();
	~Player() {};

	void Update(const float& dt);
	void UpdateKeyboardInput(const float& dt);
	void UpdateMouseInput();

	glm::mat4 GetViewMatrix();

};