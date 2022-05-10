#include "HudManager.h"

namespace Game {

	HudManager::HudManager(Game::Player& player, GLuint textureLife, GLuint textureShield) : player(player)
	{
		this->textureLife = textureLife;
		this->textureShield = textureShield;
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

				glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M_life));

				glEnableVertexAttribArray(shaderProgram->a("vertex"));
				glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, LifeInternal::vertices);

				glEnableVertexAttribArray(shaderProgram->a("texCoord"));
				glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, LifeInternal::texCoords);

				glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, textureLife);
				glUniform1i(shaderProgram->u("tex"), 0);

				glDrawArrays(GL_TRIANGLES, 0, LifeInternal::vertexCount);

				glDisableVertexAttribArray(shaderProgram->a("vertex"));

			}
		}

		if (player.isProtected()) {
			glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(0.875f, 0.4f, 0.0f));

			M = glm::scale(M, glm::vec3(0.06f, 0.06f, 0.06f));
			M = glm::rotate(M, PI, glm::vec3(0.0f, 0.0f, 1.0f));

			glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

			glEnableVertexAttribArray(shaderProgram->a("vertex"));
			glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, LifeInternal::vertices);

			glEnableVertexAttribArray(shaderProgram->a("texCoord"));
			glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, LifeInternal::texCoords);

			glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, textureShield);
			glUniform1i(shaderProgram->u("tex"), 0);

			glDrawArrays(GL_TRIANGLES, 0, LifeInternal::vertexCount);

			glDisableVertexAttribArray(shaderProgram->a("vertex"));
		}

		glEnable(GL_DEPTH_TEST);
	}

	namespace LifeInternal {

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