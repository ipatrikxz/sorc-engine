#pragma once

#include "Camera.h"

Camera::Camera()
{
	postion = glm::vec3(0, 5, 5);
	front = glm::vec3(0, 0, 0);
	worldUp = glm::vec3(0, 1, 0);
	yaw = -90.0f;
	pitch = 0.0f;
	roll = 0.0f;
	fov = 80.0f;
	speed = 2.5f;
	maxSpeed = 10.0f;
	sensitivity = 0.1f;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(postion, postion + front, up);
}

void Camera::UpdateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
	yaw += offsetX * sensitivity;
	pitch -= offsetY * -sensitivity;

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
		postion += front * speed * dt;
	if (direction == 2) // Backward
		postion -= front * speed * dt;
	if (direction == 3) // Left
		postion -= right * speed * dt;
	if (direction == 4) // Right
		postion += right * speed * dt;
	if (direction == 5) // Up
		postion += up * speed * dt;
	if (direction == 6) // Down
		postion -= up * speed * dt;
}

void Camera::UpdateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
	UpdateMouseInput(dt, offsetX, offsetY);
	UpdateKeyboardInput(dt, direction);
}
