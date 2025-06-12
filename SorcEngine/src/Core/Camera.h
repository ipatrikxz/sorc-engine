#pragma once

#include "Common.h"

class Camera {

public:

	Camera();
	~Camera() {}

	void UpdateCameraVectors();

	// input
	void mouseLook(const double& offsetX, const double& offsetY);
	void moveCamera(const float& delta, const int direction);

	void moveForward(float delta);
	void moveBackward(float delta);
	void moveRight(float delta);
	void moveLeft(float delta);
	void moveUp(float delta);
	void moveDown(float delta);

	void setAspectRatio(float aspect);

	glm::mat4 getProjectionMatrix() { return projection; }
	glm::mat4 getViewMatrix();
	glm::vec3 getLocation() const;

private:

	glm::vec3 location;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float roll;
	float fov;
	float speed;
	float maxSpeed;
	float sensitivity;

	glm::mat4 viewMatrix;
	glm::mat4 projection;
	
	float aspectRatio;

};