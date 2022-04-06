#include "Ghost.h"

namespace Entity {

	Ghost::Ghost(GLuint texture, glm::mat4 position)
	{
		this->texture = texture;
		this->position = position;

		this->position = glm::scale(this->position, glm::vec3(2.0f, 2.0f, 2.0f));
	}

	Ghost::~Ghost()
	{
	}

	void Ghost::draw(ShaderProgram* shaderProgram)
	{
		glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(position));

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
		if (test == 0 && position[3][0] >= 8.0f) {
			test = 1;
		} else if(test == 1 && position[3][0] <= -10.0f) {
			test = 0;
		}

		float speed = 2 * deltaTime;

		if (test == 0) {
			position = glm::translate(position, glm::vec3(speed, 0.0f, 0.0f));
		} else {
			position = glm::translate(position, glm::vec3(-speed, 0.0f, 0.0f));
		}
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