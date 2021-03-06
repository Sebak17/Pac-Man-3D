#ifndef TILE_FLOOR_H
#define TILE_FLOOR_H

#include <glm/gtc/type_ptr.hpp>

#include "../shaderprogram.h"
#include "../RenderHelper.h"

namespace Map {

	using namespace std;
	using namespace glm;

	class TileFloor {

		public:
			TileFloor(GLuint texture, glm::vec3 position);
			virtual ~TileFloor();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);

		private:
			GLuint texture;

			glm::vec3 position;
	};

	namespace TileFloorInternal {
		extern float vertices[];
		extern float normalCoords[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}


#endif