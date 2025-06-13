#pragma once

#include "Common.h"

class Camera {

public:

	Camera();
	~Camera() {}

	void UpdateCameraVectors();

	// input
	void lookCamera(const double& offsetX, const double& offsetY);
	void moveCamera(const float& delta, const glm::vec3 direction);

	void setAspectRatio(float aspect);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix() const { return projection; }
	
	glm::vec3 getFront() const		{ return front; }
	glm::vec3 getRight() const		{ return right; }
	glm::vec3 getUp() const			{ return up; }
	glm::vec3 getLocation() const	{ return location; }
	glm::vec3 getRotation() const	{ return glm::vec3(pitch, yaw, roll); }

	// why the fuck i didnt used this earlier?
	static Camera* getInstance() {
		static Camera instance;
		return &instance;
	}

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
	float aspectRatio;

	glm::mat4 viewMatrix;
	glm::mat4 projection;
	

};