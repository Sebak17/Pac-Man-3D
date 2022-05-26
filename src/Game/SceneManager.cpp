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

		renderObjectWithSingleTexture(shaderProgram, M, TextInternal::vertices, TextInternal::texCoords, TextInternal::vertexCount, texture);
	}

	glm::mat4 SceneManager::getPosition()
	{
		glm::mat4 M = glm::mat4(1.0f);
		
		M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

		M = glm::rotate(M, PI, glm::vec3(0.0f, 0.0f, 1.0f));

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