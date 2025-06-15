
#include "Camera.h"

#include "glm/glm.hpp"

Camera::Camera()
{
	location = glm::vec3(0.0f, 1.0f, -5.0f);
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	yaw = 90.0f;
	pitch = 0.0f;
	roll = 0.0f;
	speed = 2.5f;
	maxSpeed = 15.0f;
	sensitivity = 0.1f;
	projection = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
	
	UpdateCameraVectors();
	lookCamera(0.0, 0.0);
}

void Camera::UpdateCameraVectors()
{
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(location, location + front, up);
}

void Camera::lookCamera(const double& offsetX, const double& offsetY)
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

void Camera::moveCamera(const float& dt, const glm::vec3 direction)
{
	// convert input directions to world space using camera's orientation
	glm::vec3 worldDirection =
		front	* direction.z +     // forward/backward
		right	* direction.x +     // left/right  
		up		* direction.y;      // up/down
	
	// normalize the input direction just in case
	worldDirection = glm::normalize(worldDirection);

	// finally, move the camera in the world space direction
	location += worldDirection * speed * dt;
}

void Camera::setAspectRatio(float aspect)
{
	aspectRatio = aspect;
	projection = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
}

glm::mat4 Camera::getViewMatrix()
{
	UpdateCameraVectors();
	return viewMatrix;
}

