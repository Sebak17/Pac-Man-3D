
#ifndef GHOST_H
#define GHOST_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "shaderprogram.h"
#include "models/ModelGhost.h"

namespace Entity {

	using namespace std;
	using namespace glm;

	class Ghost {
		public:
			Ghost(GLuint texture, glm::mat4 position);
			virtual ~Ghost();

			virtual void draw(ShaderProgram* shaderProgram);
			virtual void move(float deltaTime);
		private:
			int		test = 0;
			GLuint texture;

			glm::mat4 position;
	};

	namespace TileWallInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif