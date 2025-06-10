#pragma once

#include "Common.h"

class Camera {

public:

	Camera(const glm::vec3& in_location, float in_yaw, float in_pitch);
	~Camera() {}

	void UpdateCameraVectors();
	void UpdateMouseInput(const double& offsetX, const double& offsetY);
	void UpdateKeyboardInput(const float& dt, const int direction);

	glm::mat4 GetViewMatrix() {
		viewMatrix = glm::lookAt(location, location + front, up);
		UpdateCameraVectors();
		return viewMatrix;
	}

	glm::vec3 GetPosition() const {
		return location;
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

private:
	glm::mat4 viewMatrix;

	glm::vec3 location;
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



};