
#include "TileWall.h"

namespace Map {

	TileWall tileWall;

	TileWall::TileWall() {
		vertices = TileWallInternal::vertices;
		texCoords = TileWallInternal::texCoords;
		vertexCount = TileWallInternal::vertexCount;
	}

	TileWall::~TileWall()
	{
	}

	void TileWall::draw(GLuint texture)
	{
		glEnableVertexAttribArray(spTextured->a("vertex"));
		glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, vertices);

		glEnableVertexAttribArray(spTextured->a("texCoord"));
		glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);

		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(spTextured->u("tex"), 0);

		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		glDisableVertexAttribArray(spTextured->a("vertex"));
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