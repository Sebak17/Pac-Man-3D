#include "Camera.h"

namespace Game {
	
	Camera::Camera() {

	}

	Camera::~Camera()
	{
	}

	glm::mat4 Camera::getV()
	{

		return glm::lookAt(pos, pos + DirFront, DirUp);
	}

	void Camera::update()
	{
		glm::vec3 newFront;
		newFront.x = cos(glm::radians(currentPitch)) * cos(glm::radians(currentYaw));
		newFront.y = sin(glm::radians(currentPitch));
		newFront.z = cos(glm::radians(currentPitch)) * sin(glm::radians(currentYaw));
		DirFront = glm::normalize(newFront);

		vec3 newPos = pos + (currentSpeedMove * DirFront);

		this->tmpCheckCollisions(newPos, pos);

		pos = newPos;

		currentYaw += currentSpeedRotate;


		//printf("M: %s\n", glm::to_string(pos).c_str());
	}

	void Camera::move(int key, int action)
	{

		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_LEFT) {
				currentSpeedRotate = -MAX_SPEED_YAW;
			}
			if (key == GLFW_KEY_RIGHT) {
				currentSpeedRotate = MAX_SPEED_YAW;
			}
			if (key == GLFW_KEY_UP) {
				currentSpeedMove = MAX_SPEED_POS;
			}
			if (key == GLFW_KEY_DOWN) {
				currentSpeedMove = -MAX_SPEED_POS;
			}
		}
		if (action == GLFW_RELEASE) {
			if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
				currentSpeedRotate = 0;
			}
			if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
				currentSpeedMove = 0;
			}
		}

	}

	void Camera::tmpCheckCollisions(glm::vec3& newPos, glm::vec3& pos)
	{
		if (newPos.x <= -0.85f) {
			newPos.x = pos.x;
		}

		if (newPos.z <= -0.85f) {
			newPos.z = pos.z;
		}

		if (newPos.x >= 18.85f) {
			newPos.x = pos.x;
		}

		if (newPos.z >= 18.85f) {
			newPos.z = pos.z;
		}
	}

}