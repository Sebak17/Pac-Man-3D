#include "Torch.h"

namespace Map {

	Torch::Torch(GLuint texture, glm::vec3 position, WallDirection torchDirection)
	{
		this->texture = texture;
		this->position = position;
		this->torchDirection = torchDirection;
	}

	Torch::~Torch()
	{
	}

	void Torch::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = glm::translate(M, this->position);
		M = glm::rotate(M, this->torchDirection * 90.0f * PI / 180.0f, glm::vec3(0.0f, -1.0f, 0.0f));

		M = glm::scale(M, glm::vec3(0.6f, 0.6f, 0.6f));
		M = glm::rotate(M, -100.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		M = glm::translate(M, glm::vec3(0.0f, -0.15f, -1.5f));


		renderObjectWithSingleTexture(shaderProgram, M, TorchVerts.vertCoords, TorchVerts.texCoords, TorchVerts.numVerts, texture);
	}

}