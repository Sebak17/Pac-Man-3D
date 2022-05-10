#ifndef HUD_MANAGER_H
#define HUD_MANAGER_H

#include <glm/gtc/type_ptr.hpp>
#include "../constants.h"
#include "../shaderprogram.h"
#include "Player.h"

namespace Game {

	using namespace std;

	class HudManager {

		public:
			HudManager(Game::Player& player, GLuint textureLife, GLuint textureShield);
			virtual ~HudManager();

			virtual void render(ShaderProgram* shaderProgram);

		private:
			Game::Player& player;

			GLuint textureLife, textureShield;

	};

	namespace LifeInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif