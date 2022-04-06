
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

namespace Entity {

	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
	};

	using namespace std;
	using namespace glm;

	class Ghost {

		public:
			Ghost(GLuint texture, glm::vec3 position);
			virtual ~Ghost();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);
			virtual void move(float deltaTime);

		private:
			GLuint texture;

			Direction currentDirection = NORTH;

			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::mat4 getPosition(glm::mat4 M);
			
	};

	namespace TileWallInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif