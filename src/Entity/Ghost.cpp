#include "Ghost.h"

namespace Entity {

	Ghost::Ghost(glm::vec3 position)
	{
		this->curPosition = position;
		this->dstPosition = position;

		srand(time(NULL));
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
		float speed = 1.5 * deltaTime;

		if (curPosition.x == dstPosition.x && curPosition.z == dstPosition.z) {
			dstPosition = this->findNextPosition();
		}

		if (curDirection != dstDirection) {
		
			rotate.y += deltaTime * 100;
			rotate.y = fmodf(rotate.y, 360);

			float dstAngle = dstDirection * 90.0f;
			if (rotate.y > (dstAngle - 3.0) && rotate.y < (dstAngle + 3.0)) {
				rotate.y = dstAngle;
				curDirection = dstDirection;
			}

		}
		else {

			if (dstPosition.x > curPosition.x) {

				curPosition.x += speed;
				if (curPosition.x > dstPosition.x) curPosition.x = dstPosition.x;

			}
			else if (dstPosition.x < curPosition.x) {

				curPosition.x -= speed;
				if (curPosition.x < dstPosition.x) curPosition.x = dstPosition.x;

			}
			else if (dstPosition.z > curPosition.z) {

				curPosition.z += speed;
				if (curPosition.z > dstPosition.z) curPosition.z = dstPosition.z;

			}
			else if (dstPosition.z < curPosition.z) {

				curPosition.z -= speed;
				if (curPosition.z < dstPosition.z) curPosition.z = dstPosition.z;

			}

		}
		

		if (tmpYMove > 0 && this->curPosition.y >= 0.3) {
			tmpYMove *= -1;
		} else if (tmpYMove < 0 && this->curPosition.y <= 0.0) {
			tmpYMove *= -1;
		}
		curPosition.y += tmpYMove;

	}

	glm::mat4 Ghost::getPosition(glm::mat4 M)
	{
		M = glm::translate(M, this->curPosition);


		if (this->rotate.x != 0) {
			M = glm::rotate(M, this->rotate.x * PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (this->rotate.y != 0) {
			M = glm::rotate(M, this->rotate.y * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (this->rotate.z != 0) {
			M = glm::rotate(M, this->rotate.z * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}


		M = glm::scale(M, glm::vec3(1.5f, 1.5f, 1.5f));

		return M;
	}

	glm::vec3 Ghost::findNextPosition()
	{
		// TODO: add checking walls
		int i = rand() % 4 + 1;

		switch (i)
		{
			case 1:
				dstDirection = NORTH;
				return glm::vec3(this->curPosition.x + 2, 0.0f, this->curPosition.z);

			case 2:
				dstDirection = SOUTH;
				return glm::vec3(this->curPosition.x - 2, 0.0f, this->curPosition.z);

			case 3:
				dstDirection = EAST;
				return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z + 2);

			case 4:
				dstDirection = WEST;
				return glm::vec3(this->curPosition.x, 0.0f, this->curPosition.z - 2);

		}


		
	}

}