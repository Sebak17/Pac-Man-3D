
#ifndef TILE_FLOOR_H
#define TILE_FLOOR_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "../constants.h"
#include "../shaderprogram.h"

namespace Map {

	using namespace std;
	using namespace glm;

	namespace TileFloorInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

	class TileFloor {
		public:
			int vertexCount;
			float* vertices;
			float* texCoords;

			TileFloor();
			virtual ~TileFloor();

			virtual void draw(GLuint texture);
	};

	extern TileFloor tileFloor;


}


#endif