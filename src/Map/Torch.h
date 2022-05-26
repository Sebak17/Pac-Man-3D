#ifndef TORCH_H
#define TORCH_H

#include <glm/gtc/type_ptr.hpp>

#include "../constants.h"
#include "../shaderprogram.h"
#include "../Model/ModelTorch.h"
#include "TileWall.h"
#include "../RenderHelper.h"

namespace Map {

	using namespace std;
	using namespace glm;

	class Torch {

		public:
			glm::vec3 position;
			WallDirection torchDirection;

			Torch(GLuint texture, glm::vec3 position, WallDirection torchDirection);
			virtual ~Torch();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);

		private:
			GLuint texture;

	};

}

#endif