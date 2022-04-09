#include "Ghost.h"

namespace Entity {

	Ghost::Ghost(glm::vec3 position)
	{
		this->position = position;
	}

	Ghost::~Ghost()
	{
	}

	void Ghost::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		M = this->getPosition(M);

		glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, GhostVerts.vertCoords);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, GhostVerts.normalCoords);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, GhostVerts.texCoords);

		glDrawArrays(GL_TRIANGLES, 0, GhostVerts.numVerts);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Ghost::move(float deltaTime)
	{
		float speed = 2 * deltaTime;

		if (currentDirection == NORTH && position.z >= 18.0f) {
			currentDirection = SOUTH;
		} else if(currentDirection == SOUTH && position.z <= 0.0f) {
			currentDirection = NORTH;
		}

		
		if (currentDirection == NORTH) {
			position.z += speed;
		} else {
			position.z += -speed;
		}

		rotate.y = fmodf(rotate.y + speed * 100, 360);




		if (tmpYMove > 0 && this->position.y >= 0.3) {
			tmpYMove *= -1;
		} else if (tmpYMove < 0 && this->position.y <= 0.0) {
			tmpYMove *= -1;
		}
		position.y += tmpYMove;

	}

	glm::mat4 Ghost::getPosition(glm::mat4 M)
	{
		M = glm::translate(M, this->position);


		if (this->rotate.x != 0) {
			M = glm::rotate(M, this->rotate.x * PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (this->rotate.y != 0) {
			M = glm::rotate(M, this->rotate.y * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (this->rotate.z != 0) {
			M = glm::rotate(M, this->rotate.z * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}


		M = glm::scale(M, glm::vec3(2.0f, 2.0f, 2.0f));

		return M;
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