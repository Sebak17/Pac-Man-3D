#include "TileWall.h"

namespace Map {

	TileWall::TileWall(GLuint texture, glm::vec3 position, WallDirection wallDirection)
	{
		this->texture = texture;
		this->position = position;
		this->wallDirection = wallDirection;

		vertices = TileWallInternal::vertices;
		texCoords = TileWallInternal::texCoords;
		vertexCount = TileWallInternal::vertexCount;
	}

	TileWall::~TileWall()
	{
	}

	void TileWall::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = glm::translate(M, this->position);
		M = glm::rotate(M, wallDirection * 90 * PI / 180.0f, glm::vec3(0.0f, -1.0f, 0.0f));

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


	namespace TileWallInternal {

		unsigned int vertexCount = 6;

		float vertices[] = {
			1.0f,-1.0f,-1.0f,1.0f,
			-1.0f,1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,-1.0f,1.0f,

			1.0f,-1.0f,-1.0f,1.0f,
			-1.0f,1.0f,-1.0f,1.0f,
			1.0f,1.0f,-1.0f,1.0f,
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