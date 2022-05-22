#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <glm/gtc/type_ptr.hpp>
#include "../constants.h"
#include "../shaderprogram.h"

namespace Game {

	using namespace std;

	class SceneManager {

		public:
			SceneManager(GLuint textureMenu, GLuint textureDefeat, GLuint textureVictory);
			virtual ~SceneManager();

			virtual void renderMenu(ShaderProgram* shaderProgram);
			virtual void renderDefeat(ShaderProgram* shaderProgram);
			virtual void renderVictory(ShaderProgram* shaderProgram);

		private:
			GLuint textureMenu, textureDefeat, textureVictory;

			virtual glm::mat4 getPosition();

			virtual void renderImage(ShaderProgram* shaderProgram, GLuint texture);
	};

	namespace TextInternal {
		extern float vertices[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

}

#endif