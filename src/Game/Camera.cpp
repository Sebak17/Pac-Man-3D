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

		return glm::lookAt(position, position + directionFront, directionUp);
	}

	void Camera::update()
	{
		vec3 dirFrontTmp = directionFront;
		dirFrontTmp.y = 0;

		vec3 moveVector = (currentSpeedMove * dirFrontTmp) + (glm::normalize(glm::cross(dirFrontTmp, directionUp)) * currentSpeedRotate);

		if (glm::length(moveVector) > 0.1f) {
			moveVector /= 1.5;
		}
		

		vec3 newPos = position + moveVector;

		this->checkWallsCollisions(newPos, this->position);

		this->position = newPos;
	}

	void Camera::move(int key, int action)
	{

		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_A) {
				currentSpeedRotate = -MAX_SPEED_POS;
			}
			if (key == GLFW_KEY_D) {
				currentSpeedRotate = MAX_SPEED_POS;
			}
			if (key == GLFW_KEY_W) {
				currentSpeedMove = MAX_SPEED_POS;
			}
			if (key == GLFW_KEY_S) {
				currentSpeedMove = -MAX_SPEED_POS;
			}
		}
		if (action == GLFW_RELEASE) {
			if ((key == GLFW_KEY_A && currentSpeedRotate == -MAX_SPEED_POS) || (key == GLFW_KEY_D && currentSpeedRotate == MAX_SPEED_POS)) {
				currentSpeedRotate = 0;
			}
			if ((key == GLFW_KEY_W && currentSpeedMove == MAX_SPEED_POS) || (key == GLFW_KEY_S && currentSpeedMove == -MAX_SPEED_POS)) {
				currentSpeedMove = 0;
			}
		}

	}

	void Camera::moveMouse(float posX, float posY)
	{
		if (firstMouseMove)
		{
			firstMouseMove = false;
			this->lastMousePos.x = posX;
			this->lastMousePos.y = posY;
		}

		float xoffset = (posX - this->lastMousePos.x) * SENSITIVITY;
		float yoffset = (this->lastMousePos.y - posY) * SENSITIVITY;


		this->lastMousePos.x = posX;
		this->lastMousePos.y = posY;
		this->currentYaw += xoffset;
		this->currentPitch += yoffset;

		this->currentPitch = std::min(this->currentPitch, 89.0f);
		this->currentPitch = std::max(this->currentPitch, -89.0f);

		glm::vec3 front;
		front.x = cos(glm::radians(this->currentYaw)) * cos(glm::radians(this->currentPitch));
		front.y = sin(glm::radians(this->currentPitch));
		front.z = sin(glm::radians(this->currentYaw)) * cos(glm::radians(this->currentPitch));
		directionFront = glm::normalize(front);

	}

	void Camera::checkWallsCollisions(glm::vec3& newPos, glm::vec3& prevPos)
	{

		for (auto& wall : mapManager.walls) {

			if (wall.wallDirection == Map::WallDirection::NORTH) {

				float dX = abs((wall.position.x + 0.9f) - newPos.x);
				if ((newPos.z >= (wall.position.z - 1.15f) && newPos.z <= (wall.position.z + 1.15f)) && dX <= 0.15f) {
					newPos.x = prevPos.x;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::SOUTH) {

				float dX = abs((wall.position.x - 0.9f) - newPos.x);
				if ((newPos.z >= (wall.position.z - 1.15f) && newPos.z <= (wall.position.z + 1.15f)) && dX <= 0.2f) {
					newPos.x = prevPos.x;
					break;
				}

			}

			// ------------------------[ WALLS SIDES ]-----------------------
			if (wall.wallDirection == Map::WallDirection::EAST) {

				float dX = abs(wall.position.x - newPos.x) - 1.0f;
				if ((newPos.z >= ((wall.position.z + 1.0f) - 0.25f) && newPos.z <= ((wall.position.z + 1.0f) + 0.05f)) && dX <= 0.15f) {
					newPos.x = prevPos.x;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::WEST) {

				float dX = abs(wall.position.x - newPos.x) - 1.0f;
				if ((newPos.z >= ((wall.position.z - 1.0f) - 0.05f) && newPos.z <= ((wall.position.z - 1.0f) + 0.25f)) && dX <= 0.15f) {
					newPos.x = prevPos.x;
					break;
				}

			}
			// --------------------------------------------------------------

		}

		for (auto& wall : mapManager.walls) {

			if (wall.wallDirection == Map::WallDirection::EAST) {

				float dZ = abs((wall.position.z + 0.9f) - newPos.z);
				if ((newPos.x >= (wall.position.x - 1.15f) && newPos.x <= (wall.position.x + 1.15f)) && dZ <= 0.2f) {
					newPos.z = prevPos.z;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::WEST) {

				float dZ = abs((wall.position.z - 0.9f) - newPos.z);
				if ((newPos.x >= (wall.position.x - 1.15f) && newPos.x <= (wall.position.x + 1.15f)) && dZ <= 0.2f) {
					newPos.z = prevPos.z;
					break;
				}

			}

			// ------------------------[ WALLS SIDES ]-----------------------
			if (wall.wallDirection == Map::WallDirection::NORTH) {

				float dZ = abs(wall.position.z - newPos.z) - 1.0f;
				if ((newPos.x >= ((wall.position.x + 1.0f) - 0.22f) && newPos.x <= ((wall.position.x + 1.0f) + 0.05f)) && dZ <= 0.15f) {
					newPos.z = prevPos.z;
					break;
				}

			}

			if (wall.wallDirection == Map::WallDirection::SOUTH) {

				float dZ = abs(wall.position.z - newPos.z) - 1.0f;
				if ((newPos.x >= ((wall.position.x - 1.0f) - 0.05f) && newPos.x <= ((wall.position.x - 1.0f) + 0.27f)) && dZ <= 0.15f) {
					newPos.z = prevPos.z;
					break;
				}

			}
			// --------------------------------------------------------------


		}

	}

	bool Camera::checkGhostsCollisions()
	{
		for (auto& ghost : mapData.ghosts)
		{
			float d = distance(this->position, ghost.curPosition);
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

			float d = distance(this->position, coin.position);
			if (d < 1.0f) {
				coin.collected = true;
				return true;
			}
		}

		return false;
	}

}