#include "Ghost.h"

namespace Entity {

	Ghost::Ghost(glm::vec3 position, Map::MapManager& mapManager) : mapManager(mapManager)
	{
		this->curPosition = position;
		this->dstPosition = position;

		srand(time(NULL));
	}

	Ghost::~Ghost()
	{
	}

	void Ghost::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = this->getPosition(M);

		renderObjectWithColor(shaderProgram, M, GhostVerts.vertCoords, GhostVerts.normalCoords, GhostVerts.texCoords, GhostVerts.numVerts, 1.0f, 1.0f, 1.0f);
	}

	void Ghost::move(float deltaTime)
	{

		if (curPosition.x == dstPosition.x && curPosition.z == dstPosition.z) {
			dstPosition = this->findNextPosition();
		}

		if (curDirection != dstDirection) {
		
			if ((curDirection == 0 && dstDirection == 3) || curDirection - 1 == dstDirection) {
				rotate.y -= deltaTime * SPEED_ROTATE;

				if (rotate.y < 0) {
					rotate.y += 360;
				}
			}
			else {
				rotate.y += deltaTime * SPEED_ROTATE;
			}

			
			rotate.y = fmodf(rotate.y, 360);

			float dstAngle = dstDirection * 90.0f;
			if (rotate.y > (dstAngle - 3.0) && rotate.y < (dstAngle + 3.0)) {
				rotate.y = dstAngle;
				curDirection = dstDirection;
			}

		}
		else {

			float speed = SPEED_MOVE * deltaTime;

			if (dstPosition.x > curPosition.x) {

				curPosition.x += speed;
				if (curPosition.x > dstPosition.x) curPosition.x = dstPosition.x;

			}
			else if (dstPosition.x < curPosition.x) {

				curPosition.x -= speed;
				if (curPosition.x < dstPosition.x) curPosition.x = dstPosition.x;

			}
			else if (dstPosition.z > curPosition.z) {

				curPosition.z += speed;
				if (curPosition.z > dstPosition.z) curPosition.z = dstPosition.z;

			}
			else if (dstPosition.z < curPosition.z) {

				curPosition.z -= speed;
				if (curPosition.z < dstPosition.z) curPosition.z = dstPosition.z;

			}

		}
		

		if (tmpYMove > 0 && this->curPosition.y >= 0.3) {
			tmpYMove *= -1;
		} else if (tmpYMove < 0 && this->curPosition.y <= 0.0) {
			tmpYMove *= -1;
		}
		curPosition.y += tmpYMove;

	}

	void Ghost::revive()
	{
		int rnd_x = (std::rand() % mapManager.sizeX);
		int rnd_z = (std::rand() % mapManager.sizeZ);

		this->curPosition = glm::vec3(rnd_x * 2.0f, 0.0f, rnd_z * 2.0f);
		this->dstPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		this->rotate = glm::vec3(0.0f, 90.0f, 0.0f);

		this->curDirection = NORTH;
		this->dstDirection = NONE;
	}

	glm::mat4 Ghost::getPosition(glm::mat4 M)
	{
		M = glm::translate(M, this->curPosition);


		if (this->rotate.x != 0) {
			M = glm::rotate(M, this->rotate.x * PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (this->rotate.y != 0) {
			M = glm::rotate(M, this->rotate.y * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (this->rotate.z != 0) {
			M = glm::rotate(M, this->rotate.z * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}


		M = glm::scale(M, glm::vec3(1.5f, 1.5f, 1.5f));

		return M;
	}

	glm::vec3 Ghost::findNextPosition()
	{
		vector<int> directionAvailable;
		directionAvailable.push_back(Map::WallDirection::NORTH);
		directionAvailable.push_back(Map::WallDirection::EAST);
		directionAvailable.push_back(Map::WallDirection::SOUTH);
		directionAvailable.push_back(Map::WallDirection::WEST);

		int blockedDir;
		if (this->curDirection == Direction::NORTH) {
			blockedDir = Map::WallDirection::SOUTH;
		}
		else if (this->curDirection == Direction::EAST) {
			blockedDir = Map::WallDirection::WEST;
		}
		else if (this->curDirection == Direction::SOUTH) {
			blockedDir = Map::WallDirection::NORTH;
		}
		else if (this->curDirection == Direction::WEST) {
			blockedDir = Map::WallDirection::EAST;
		}

		directionAvailable.erase(std::remove(directionAvailable.begin(), directionAvailable.end(), blockedDir), directionAvailable.end());

		for (auto& wall : mapManager.walls) {
			if (wall.position.x != this->curPosition.x || wall.position.z != this->curPosition.z) {
				continue;
			}

			directionAvailable.erase(std::remove(directionAvailable.begin(), directionAvailable.end(), wall.wallDirection), directionAvailable.end());
		}

		if (directionAvailable.size() == 0) {
			printf("Ghost found a path problem! X: %f Z: %f\n", this->curPosition.x, this->curPosition.z);
			this->curDirection = Direction::NONE;
			this->dstDirection = Direction::NONE;
			return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z);
		}

		int newDirPos = directionAvailable[rand() % directionAvailable.size()];

		switch (newDirPos)
		{
			case 1:
				dstDirection = Direction::NORTH;
				return glm::vec3(this->curPosition.x + 2, 0.0f, this->curPosition.z);

			case 3:
				dstDirection = Direction::SOUTH;
				return glm::vec3(this->curPosition.x - 2, 0.0f, this->curPosition.z);

			case 2:
				dstDirection = Direction::EAST;
				return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z + 2);

			case 0:
				dstDirection = Direction::WEST;
				return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z - 2);
		}

		return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z);
	}

}