#include "TileFloor.h"

namespace Map {

	TileFloor::TileFloor(GLuint texture, glm::vec3 position)
	{
		this->texture = texture;
		this->position = position;

		vertices = TileFloorInternal::vertices;
		texCoords = TileFloorInternal::texCoords;
		vertexCount = TileFloorInternal::vertexCount;
	}

	TileFloor::~TileFloor()
	{
	}

	void TileFloor::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = glm::translate(M, this->position);

		glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(shaderProgram->a("vertex"));
		glVertexAttribPointer(shaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, vertices);

		glEnableVertexAttribArray(shaderProgram->a("texCoord"));
		glVertexAttribPointer(shaderProgram->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(shaderProgram->u("tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		glDisableVertexAttribArray(shaderProgram->a("vertex"));
	}


	namespace TileFloorInternal {

		unsigned int vertexCount = 6;

		float vertices[] = {
			1.0f,-1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,1.0f,1.0f,
			-1.0f,-1.0f,-1.0f,1.0f,

			1.0f,-1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,1.0f,1.0f,
			1.0f,-1.0f,1.0f,1.0f,
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