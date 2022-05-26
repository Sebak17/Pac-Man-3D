#include "HudManager.h"

namespace Game {

	HudManager::HudManager(Game::Player& player, GLuint textureLife, GLuint textureShield, GLuint textureSword) : player(player)
	{
		this->textureLife = textureLife;
		this->textureShield = textureShield;
		this->textureSword = textureSword;
	}

	HudManager::~HudManager()
	{
	}

	void HudManager::render(ShaderProgram* shaderProgram)
	{
		glDisable(GL_DEPTH_TEST);

		{
			glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.95f, 0.41f, 0.0f));

			for (int i = 0; i < player.livesCount; i++)
			{
				M = glm::translate(M, glm::vec3(0.073f, 0.0f, 0.0f));

				glm::mat4 M_life = glm::scale(M, glm::vec3(0.032f, 0.032f, 0.032f));
				M_life = glm::rotate(M_life, PI, glm::vec3(0.0f, 0.0f, 1.0f));

				renderObjectWithSingleTexture(shaderProgram, M_life, ItemInternal::vertices, ItemInternal::texCoords, ItemInternal::vertexCount, textureLife);
			}
		}

		if (player.isProtected()) {
			glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(0.875f, 0.4f, 0.0f));

			M = glm::scale(M, glm::vec3(0.06f, 0.06f, 0.06f));
			M = glm::rotate(M, PI, glm::vec3(0.0f, 0.0f, 1.0f));

			renderObjectWithSingleTexture(shaderProgram, M, ItemInternal::vertices, ItemInternal::texCoords, ItemInternal::vertexCount, textureShield);
		}

		if (player.isAttackMode()) {
			glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(0.875f, 0.3f, 0.0f));

			M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));
			M = glm::rotate(M, PI, glm::vec3(0.0f, 0.0f, 1.0f));

			renderObjectWithSingleTexture(shaderProgram, M, ItemInternal::vertices, ItemInternal::texCoords, ItemInternal::vertexCount, textureSword);
		}

		glEnable(GL_DEPTH_TEST);
	}

	namespace ItemInternal {

		unsigned int vertexCount = 6;

		float vertices[] = {
			1.0f,-1.0f,0.0f,1.0f,
			-1.0f,1.0f,0.0f,1.0f,
			-1.0f,-1.0f,0.0f,1.0f,

			1.0f,-1.0f,0.0f,1.0f,
			-1.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,0.0f,1.0f,
		};

		float texCoords[] = {
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
		};

	}

}