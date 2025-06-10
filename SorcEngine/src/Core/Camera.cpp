
#include "Camera.h"

Camera::Camera(const glm::vec3& in_location, float in_yaw, float in_pitch)
{
	location = in_location;
	front = glm::vec3(1.0f, 0.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = in_yaw;
	pitch = in_pitch;
	roll = 0.0f;
	speed = 2.5f;
	maxSpeed = 15.0f;
	sensitivity = 0.1f;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(location, location + front, up);
}

void Camera::UpdateMouseInput(const double& offsetX, const double& offsetY)
{
	yaw += static_cast<glm::float32>(offsetX) * sensitivity;
	pitch -= static_cast<glm::float32>(offsetY) * -sensitivity;

	if (pitch > 89.0f)	pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateKeyboardInput(const float& dt, const int direction)
{
	if (direction == 1) // Forward
		location += front * speed * dt;
	if (direction == 2) // Backward
		location -= front * speed * dt;
	if (direction == 3) // Left
		location -= right * speed * dt;
	if (direction == 4) // Right
		location += right * speed * dt;
	if (direction == 5) // Up
		location += up * speed * dt;
	if (direction == 6) // Down
		location -= up * speed * dt;
}

