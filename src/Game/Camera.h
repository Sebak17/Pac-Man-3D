#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../constants.h"
#include "Loader.h"

namespace Game {

	using namespace std;
	using namespace glm;

	const float MAX_SPEED_POS = PI / 30;
	const float MAX_SPEED_YAW = PI / 2 * 1.25f;

	class Camera {

		public:
			Camera(Map::MapManager& mapManager);
			virtual ~Camera();

			glm::vec3 pos		= glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 DirFront	= glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3 DirUp		= glm::vec3(0.0f, 1.0f, 0.0f);

			virtual glm::mat4 getV();
			virtual void update();
			virtual void move(int key, int action);

		private:
			Map::MapManager& mapManager;

			float currentSpeedRotate = 0.0f;
			float currentSpeedMove = 0.0f;
			float currentYaw = 0.0f;
			float currentPitch = 0.0f;

			void checkWallsCollisions(glm::vec3& newPos, glm::vec3& pos);
	};

}


#endif