#include "Coin.h"

namespace Entity {

	Coin::Coin(glm::vec3 position)
	{
		this->position = position;

		this->collected = false;
	}

	Coin::~Coin()
	{
	}

	void Coin::draw(ShaderProgram* shaderProgram, glm::mat4 M)
	{
		if (this->collected) {
			return;
		}

		M = this->getPosition(M);

		renderObjectWithColor(shaderProgram, M, CoinVerts.vertCoords, CoinVerts.normalCoords, CoinVerts.texCoords, CoinVerts.numVerts, 0.8313f, 0.6862f, 0.0196f);
	}

	void Coin::update(float deltaTime)
	{
		
		rotate.y += 40 * deltaTime;

	}

	glm::mat4 Coin::getPosition(glm::mat4 M)
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

		M = glm::translate(M, glm::vec3(0.0f, -0.55f, 0.0f));

		M = glm::scale(M, glm::vec3(0.4f, 0.4f, 0.4f));

		return M;
	}

}