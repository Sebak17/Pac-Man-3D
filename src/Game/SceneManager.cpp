#include "SceneManager.h"

namespace Game {

	SceneManager::SceneManager(GLuint textureMenu, GLuint textureDefeat, GLuint textureVictory)
	{
		this->textureMenu = textureMenu;
		this->textureDefeat = textureDefeat;
		this->textureVictory = textureVictory;
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::renderMenu(ShaderProgram* shaderProgram)
	{
		this->renderImage(shaderProgram, this->textureMenu);
	}

	void SceneManager::renderDefeat(ShaderProgram* shaderProgram)
	{
		this->renderImage(shaderProgram, this->textureDefeat);
	}

	void SceneManager::renderVictory(ShaderProgram* shaderProgram)
	{
		this->renderImage(shaderProgram, this->textureVictory);
	}

	void SceneManager::renderImage(ShaderProgram* shaderProgram, GLuint texture)
	{
		glm::mat4 M = this->getPosition();

		glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(shaderProgram->a("vertex"));
		glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, TextInternal::vertices);

		glEnableVertexAttribArray(shaderProgram->a("texCoord"));
		glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, TextInternal::texCoords);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(shaderProgram->u("tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, TextInternal::vertexCount);

		glDisableVertexAttribArray(shaderProgram->a("vertex"));
	}

	glm::mat4 SceneManager::getPosition()
	{
		glm::mat4 M = glm::mat4(1.0f);
		
		M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

		return M;
	}

	namespace TextInternal {

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