#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <glm/gtc/type_ptr.hpp>
#include "../constants.h"
#include "../shaderprogram.h"

namespace Game {

	using namespace std;

	class SceneManager {

		public:
			SceneManager();
			virtual ~SceneManager();

			virtual void renderMenu(ShaderProgram* shaderProgram);
			virtual void renderDefeat(ShaderProgram* shaderProgram);
			virtual void renderVictory(ShaderProgram* shaderProgram);

		private:

	};

}

#endif