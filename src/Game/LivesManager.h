#ifndef LIVES_MANAGER_H
#define LIVES_MANAGER_H

#include <glm/gtc/type_ptr.hpp>
#include "../constants.h"
#include "../shaderprogram.h"
#include "Player.h"

namespace Game {

	using namespace std;

	class LivesManager {

		public:
			LivesManager(Game::Player& player, GLuint texture);
			virtual ~LivesManager();

			virtual void render(ShaderProgram* shaderProgram);

		private:
			Game::Player& player;

			GLuint texture;

	};

	namespace LifeInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif