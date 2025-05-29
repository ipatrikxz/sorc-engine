#pragma once

#include "../Common.h"

class Camera {

private:
	glm::mat4 viewMatrix;

	glm::vec3 position;
	glm::vec3 worldUp;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	glm::float32 yaw;
	glm::float32 pitch;
	glm::float32 roll;

	glm::float32 fov;
	glm::float32 speed;
	glm::float32 maxSpeed;
	glm::float32 sensitivity;

public:

	Camera();
	~Camera() {}
	
	glm::mat4 GetViewMatrix() {
		viewMatrix = glm::lookAt(position, position + front, up);
		UpdateCameraVectors();
		return viewMatrix;
	}

	void UpdateCameraVectors();
	void UpdateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
	void UpdateKeyboardInput(const float& dt, const int direction);
	void UpdateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);

	glm::vec3 GetPosition() const {
		return position;
	}

	glm::vec3 GetForwardVector() const { 
		return front; 
	}

	float GetSpeed() const {
		return speed;
	}

	void SetSpeed(const float& speed) {
		this->speed = std::clamp(speed, MIN_SPEED, MAX_SPEED);
	}

	void SetFov(const float& fov) {
		this->fov = std::clamp(fov, MIN_FOV, MAX_FOV);
	}

};