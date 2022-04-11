#include "Camera.h"

namespace Game {
	
	Camera::Camera(Map::MapManager& mapManager, Game::MapData& mapData) : mapManager(mapManager), mapData(mapData)
	{
		
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

		this->checkWallsCollisions(newPos, pos);

		this->pos = newPos;

		currentYaw += currentSpeedRotate;
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
			if ((key == GLFW_KEY_LEFT && currentSpeedRotate == -MAX_SPEED_YAW) || (key == GLFW_KEY_RIGHT && currentSpeedRotate == MAX_SPEED_YAW)) {
				currentSpeedRotate = 0;
			}
			if ((key == GLFW_KEY_UP && currentSpeedMove == MAX_SPEED_POS) || (key == GLFW_KEY_DOWN && currentSpeedMove == -MAX_SPEED_POS)) {
				currentSpeedMove = 0;
			}
		}

	}

	void Camera::checkWallsCollisions(glm::vec3& newPos, glm::vec3& prevPos)
	{
		
		// TODO: add collisions with sides of wall

		for (auto& wall : mapManager.walls) {

			if (wall.wallDirection == Map::WallDirection::NORTH) {

				float dX = abs((wall.position.x + 1) - newPos.x);
				if ((newPos.z >= (wall.position.z - 1) && newPos.z <= (wall.position.z + 1)) && dX <= 0.25) {
					newPos.x = prevPos.x;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::SOUTH) {

				float dX = abs((wall.position.x - 1) - newPos.x);
				if ((newPos.z >= (wall.position.z - 1) && newPos.z <= (wall.position.z + 1)) && dX <= 0.3) {
					newPos.x = prevPos.x;
					break;
				}

			}


		}

		for (auto& wall : mapManager.walls) {

			if (wall.wallDirection == Map::WallDirection::WEST) {

				float dZ = abs((wall.position.z - 1) - newPos.z);
				if ((newPos.x >= (wall.position.x - 1) && newPos.x <= (wall.position.x + 1)) && dZ <= 0.25) {
					newPos.z = prevPos.z;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::EAST) {

				float dZ = abs((wall.position.z + 1) - newPos.z);
				if ((newPos.x >= (wall.position.x - 1) && newPos.x <= (wall.position.x + 1)) && dZ <= 0.25) {
					newPos.z = prevPos.z;
					break;
				}

			}


		}

	}

	bool Camera::checkGhostsCollisions()
	{
		for (auto& ghost : mapData.ghosts)
		{
			float d = distance(this->pos, ghost.curPosition);
			if (d < 1.1f) {
				return true;
			}
		}

		return false;
	}

	bool Camera::checkCoinsCollisions()
	{
		for (auto& coin : mapData.coins)
		{
			if (coin.collected) {
				continue;
			}

			float d = distance(this->pos, coin.position);
			if (d < 1.0f) {
				coin.collected = true;
				return true;
			}
		}

		return false;
	}

}