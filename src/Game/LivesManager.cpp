#include "LivesManager.h"

namespace Game {

	LivesManager::LivesManager(Game::Player& player, GLuint texture) : player(player)
	{
		this->texture = texture;
	}

	LivesManager::~LivesManager()
	{
	}

	void LivesManager::render(ShaderProgram* shaderProgram)
	{
		glm::mat4 M = glm::mat4(1.0f);

		M = glm::translate(M, glm::vec3(-0.95f, 0.41f, 0.0f));
		

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

			glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(shaderProgram->u("tex"), 0);

			glDrawArrays(GL_TRIANGLES, 0, LifeInternal::vertexCount);

			glDisableVertexAttribArray(shaderProgram->a("vertex"));

		}

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