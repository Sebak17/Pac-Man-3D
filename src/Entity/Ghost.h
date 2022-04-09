
#ifndef GHOST_H
#define GHOST_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "../constants.h"
#include "../shaderprogram.h"
#include "../Model/ModelGhost.h"

#include <stdlib.h>
#include <time.h>

namespace Entity {

	enum Direction {
		NORTH = 1,
		EAST = 0,
		SOUTH = 3,
		WEST = 2,
		NONE = -1,
	};

	using namespace std;
	using namespace glm;

	class Ghost {

		public:
			Ghost(glm::vec3 position);
			virtual ~Ghost();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);
			virtual void move(float deltaTime);

		private:
			Direction curDirection = NORTH;
			Direction dstDirection = NONE;

			glm::vec3 curPosition = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 dstPosition = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::vec3 rotate = glm::vec3(0.0f, 90.0f, 0.0f);

			float tmpYMove = 0.003f;

			glm::mat4 getPosition(glm::mat4 M);

			glm::vec3 findNextPosition();
			
	};

}

#endif