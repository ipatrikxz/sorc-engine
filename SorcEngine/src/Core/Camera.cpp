
#include "Camera.h"

Camera::Camera()
{
	location = glm::vec3(0.0f, 2.0f, -2.0f);
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = 0.0f;
	pitch = -30.0f;
	roll = 0.0f;
	speed = 2.5f;
	maxSpeed = 15.0f;
	sensitivity = 0.1f;
	projection = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(location, location + front, up);
}

void Camera::mouseLook(const double& offsetX, const double& offsetY)
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

void Camera::moveCamera(const float& dt, const int direction)
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

void Camera::setAspectRatio(float aspect)
{
	aspectRatio = aspect;
	projection = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void Camera::moveForward(float delta)
{
	location += front * speed * delta;
}

void Camera::moveBackward(float delta)
{
	location -= front * speed * delta;
}

void Camera::moveRight(float delta)
{
	location += right * speed * delta;
}

void Camera::moveLeft(float delta)
{
	location -= right * speed * delta;
}

void Camera::moveUp(float delta)
{
	location += up * speed * delta;
}

void Camera::moveDown(float delta)
{
	location -= up * speed * delta;
}

glm::mat4 Camera::getViewMatrix()
{
	viewMatrix = glm::lookAt(location, location + front, up);
	UpdateCameraVectors();
	return viewMatrix;
}

glm::vec3 Camera::getLocation() const
{
	return location;
}
