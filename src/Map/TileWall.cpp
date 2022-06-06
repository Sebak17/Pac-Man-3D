#include "TileWall.h"

namespace Map {

	TileWall::TileWall(GLuint texture, glm::vec3 position, WallDirection wallDirection)
	{
		this->texture = texture;
		this->position = position;
		this->wallDirection = wallDirection;
	}

	TileWall::~TileWall()
	{
	}

	void TileWall::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = glm::translate(M, this->position);
		M = glm::rotate(M, wallDirection * 90 * PI / 180.0f, glm::vec3(0.0f, -1.0f, 0.0f));

		renderObjectWithSingleTexture(shaderProgram, M, TileWallInternal::vertices, TileWallInternal::texCoords, TileWallInternal::normalCoords, TileWallInternal::vertexCount, texture);
	}


	namespace TileWallInternal {

		unsigned int vertexCount = 18;

		float vertices[] = {
			1.0f,-1.0f,-0.9f,1.0f,
			-1.0f,1.0f,-0.9f,1.0f,
			-1.0f,-1.0f,-0.9f,1.0f,

			1.0f,-1.0f,-0.9f,1.0f,
			-1.0f,1.0f,-0.9f,1.0f,
			1.0f,1.0f,-0.9f,1.0f,

			1.0f,-1.0f,-1.0f,1.0f, // R-BR
			1.0f,1.0f,-0.9f,1.0f,  // R-TL
			1.0f,1.0f,-1.0f,1.0f,  // R-TR

			1.0f,-1.0f,-1.0f,1.0f, // R-BR
			1.0f,1.0f,-0.9f,1.0f,  // R-TL
			1.0f,-1.0f,-0.9f,1.0f, // R-BL

			-1.0f,-1.0f,-1.0f,1.0f, // L-BL
			-1.0f,1.0f,-0.9f,1.0f,  // L-TR
			-1.0f,1.0f,-1.0f,1.0f,  // L-TL

			-1.0f,-1.0f,-1.0f,1.0f, // L-BL
			-1.0f,1.0f,-0.9f,1.0f,  // L-TR
			-1.0f,-1.0f,-0.9f,1.0f, // L-BR
		};

		float normalCoords[] = {
			0.0f,0.0f,0.9f,0.0f,
			0.0f,0.0f,0.9f,0.0f,
			0.0f,0.0f,0.9f,0.0f,

			0.0f,0.0f,0.9f,0.0f,
			0.0f,0.0f,0.9f,0.0f,
			0.0f,0.0f,0.9f,0.0f,

			1.0f,0.0f,0.0f,0.0f,	// R-BR
			1.0f,0.0f,0.0f,0.0f,	// R-TL
			1.0f,0.0f,0.0f,0.0f,	// R-TR

			1.0f,0.0f,0.0f,0.0f,	// R-BR
			1.0f,0.0f,0.0f,0.0f,	// R-TL
			1.0f,0.0f,0.0f,0.0f,	// R-BL

			-1.0f,0.0f,0.0f,0.0f,	// L-BL
			-1.0f,0.0f,0.0f,0.0f,	// L-TR
			-1.0f,0.0f,0.0f,0.0f,	// L-TL

			-1.0f,0.0f,0.0f,0.0f,	// L-BL
			-1.0f,0.0f,0.0f,0.0f,	// L-TR
			-1.0f,0.0f,0.0f,0.0f,	// L-BR
		};

		float texCoords[] = {
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			0.1f, 0.0f,
			0.0f, 1.0f,
			0.1f, 1.0f,

			0.1f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			0.1f, 0.0f,
			0.0f, 1.0f,
			0.1f, 1.0f,

			0.1f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
		};

	}

}