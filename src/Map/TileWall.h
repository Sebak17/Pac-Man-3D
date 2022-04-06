
#ifndef TILE_WALL_H
#define TILE_WALL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shaderprogram.h"
#include "../constants.h"

namespace Map {

	using namespace std;
	using namespace glm;

	enum WallDirection {
		NORTH = 1,
		EAST = 2,
		SOUTH = 3,
		WEST = 0,
	};

	class TileWall {
		public:
			int vertexCount;
			float* vertices;
			float* texCoords;

			TileWall(GLuint texture, glm::vec3 position, WallDirection wallDirection);
			virtual ~TileWall();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);

		private:
			GLuint texture;

			glm::vec3 position;
			WallDirection wallDirection;
	};

	namespace TileWallInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}


#endif