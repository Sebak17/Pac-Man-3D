#ifndef COIN_H
#define COIN_H

#include <glm/gtc/type_ptr.hpp>

#include "../constants.h"
#include "../shaderprogram.h"
#include "../Model/ModelCoin.h"

namespace Entity {

	using namespace std;
	using namespace glm;

	class Coin {

		public:
			Coin(glm::vec3 position);
			virtual ~Coin();

			virtual void draw(ShaderProgram* shaderProgram, glm::mat4 M);
			virtual void update(float deltaTime);

		private:
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::mat4 getPosition(glm::mat4 M);
			
	};

}

#endif