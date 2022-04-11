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


		glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(shaderProgram->a("vertex"));
		glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, TorchVerts.vertCoords);

		glEnableVertexAttribArray(shaderProgram->a("texCoord"));
		glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, TorchVerts.texCoords);

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(shaderProgram->u("tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, TorchVerts.numVerts);

		glDisableVertexAttribArray(shaderProgram->a("vertex"));
	}

}