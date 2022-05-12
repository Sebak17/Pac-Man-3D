#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>

#include "../constants.h"
#include "Loader.h"

namespace Game {

	using namespace std;
	using namespace glm;

	const float SENSITIVITY = 0.1f;
	const float MAX_SPEED_POS = PI / 40;

	class Camera {

		public:
			glm::vec3 position;
			glm::vec3 directionFront = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 directionUp = glm::vec3(0.0f, 1.0f, 0.0f);

			Camera(Map::MapManager& mapManager, Game::MapData& mapData);
			virtual ~Camera();

			virtual glm::mat4 getV();
			virtual glm::mat4 getDefaultV();

			virtual void loadData();
			virtual void update();
			virtual void move(int key, int action);
			virtual void moveMouse(float posX, float posY);

			virtual Entity::Ghost* checkGhostsCollisions();
			virtual bool checkCoinsCollisions();
			virtual bool checkSpecialCoinsCollisions();


		private:
			Map::MapManager& mapManager;
			Game::MapData& mapData;

			float currentSpeedRotate = 0.0f;
			float currentSpeedMove = 0.0f;
			float currentYaw = 0.0f;
			float currentPitch = 0.0f;

			glm::vec2 lastMousePos;
			bool firstMouseMove = true;

			void checkWallsCollisions(glm::vec3& newPos, glm::vec3& pos);
	};

}


#endif