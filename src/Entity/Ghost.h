#ifndef GHOST_H
#define GHOST_H

#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <time.h>

#include "../constants.h"
#include "../shaderprogram.h"
#include "../Model/ModelGhost.h"
#include "../Map/MapManager.h"
#include "../RenderHelper.h"

#define SPEED_ROTATE 100
#define SPEED_MOVE   1.5

namespace Entity {

	using namespace std;
	using namespace glm;


	enum Direction {
		NORTH = 1,
		EAST = 0,
		SOUTH = 3,
		WEST = 2,
		NONE = -1,
	};


	class Ghost {

		public:
			glm::vec3 curPosition = glm::vec3(0.0f, 0.0f, 0.0f);

			Ghost(glm::vec3 position, Map::MapManager& mapManager);
			virtual ~Ghost();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);
			virtual void move(float deltaTime);

			virtual void revive();

		private:
			Map::MapManager& mapManager;

			Direction curDirection = NORTH;
			Direction dstDirection = NONE;

			glm::vec3 dstPosition = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::vec3 rotate = glm::vec3(0.0f, 90.0f, 0.0f);

			float tmpYMove = 0.003f;

			glm::mat4 getPosition(glm::mat4 M);

			glm::vec3 findNextPosition();
			
	};

}

#endif