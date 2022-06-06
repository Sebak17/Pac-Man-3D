#include "TileFloor.h"

namespace Map {

	TileFloor::TileFloor(GLuint texture, glm::vec3 position)
	{
		this->texture = texture;
		this->position = position;

	}

	TileFloor::~TileFloor()
	{
	}

	void TileFloor::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = glm::translate(M, this->position);

		renderObjectWithSingleTexture(shaderProgram, M, TileFloorInternal::vertices, TileFloorInternal::texCoords, TileFloorInternal::normalCoords, TileFloorInternal::vertexCount, texture);
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

		float normalCoords[] = {
			0.0f,1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,

			0.0f,1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
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