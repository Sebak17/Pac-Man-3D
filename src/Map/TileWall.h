
#ifndef TILE_WALL_H
#define TILE_WALL_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "../constants.h"
#include "../shaderprogram.h"

namespace Map {

	using namespace std;
	using namespace glm;

	namespace TileWallInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

	class TileWall {
		public:
			int vertexCount;
			float* vertices;
			float* texCoords;

			TileWall();
			virtual ~TileWall();

			virtual void draw(GLuint texture);
	};

	extern TileWall tileWall;


}


#endif