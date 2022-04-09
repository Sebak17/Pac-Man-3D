#ifndef TILE_WALL_H
#define TILE_WALL_H

#include <glm/gtc/type_ptr.hpp>

#include "../constants.h"
#include "../shaderprogram.h"

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

			glm::vec3 position;
			WallDirection wallDirection;

			TileWall(GLuint texture, glm::vec3 position, WallDirection wallDirection);
			virtual ~TileWall();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);

		private:
			GLuint texture;
			
	};

	namespace TileWallInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif