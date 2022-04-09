#include "Loader.h"

namespace Game {

	Loader::Loader()
	{
	}

	Loader::~Loader()
	{
	}

	void Loader::loadTextures()
	{
		textureWall = this->readTexture("assets/textures/bricks.png");
		textureFloor = this->readTexture("assets/textures/stone-wall.png");
	}

	void Loader::destroyTextures()
	{
		glDeleteTextures(1, &textureWall);
		glDeleteTextures(2, &textureFloor);
	}

	Game::MapData Loader::loadMap(const char* filename)
	{
		struct MapData mapData;

		std::ifstream file(filename);
		json gameData;
		file >> gameData;

		auto mapElements = gameData.find("map");

		for (const auto& mapElement : mapElements.value().items())
		{
			string mapElementType = mapElement.value()["type"].dump();
			float mapElementPosX = std::stof(mapElement.value()["position"]["x"].dump());
			float mapElementPosZ = std::stof(mapElement.value()["position"]["z"].dump());

			if (strcmp(mapElementType.c_str(), "\"wall\"") == 0) {
				string wallDir = mapElement.value()["position"]["direction"].dump();
				Map::WallDirection wallDirection;

				if (strcmp(wallDir.c_str(), "\"east\"") == 0) {
					wallDirection = Map::WallDirection::EAST;
				} else if(strcmp(wallDir.c_str(), "\"south\"") == 0) {
					wallDirection = Map::WallDirection::SOUTH;
				} else if(strcmp(wallDir.c_str(), "\"west\"") == 0) {
					wallDirection = Map::WallDirection::WEST;
				} else {
					wallDirection = Map::WallDirection::NORTH;
				}

				Map::TileWall wall(textureWall, glm::vec3(mapElementPosX, 0.0f, mapElementPosZ), wallDirection);
				mapData.walls.push_back(wall);
			}

			if (strcmp(mapElementType.c_str(), "\"floor\"") == 0) {
				Map::TileFloor floor(textureFloor, glm::vec3(mapElementPosX, 0.0f, mapElementPosZ));
				mapData.floors.push_back(floor);
			}

			if (strcmp(mapElementType.c_str(), "\"ceiling\"") == 0) {
				Map::TileFloor floor(textureFloor, glm::vec3(mapElementPosX, 2.0f, mapElementPosZ));
				mapData.floors.push_back(floor);
			}

		}



		auto ghostsElements = gameData.find("ghosts");

		for (const auto& ghostsElement : ghostsElements.value().items())
		{
			float ghostPosX = std::stof(ghostsElement.value()["position"]["x"].dump());
			float ghostPosZ = std::stof(ghostsElement.value()["position"]["z"].dump());

			Entity::Ghost ghost(glm::vec3(ghostPosX, 0.0f, ghostPosZ));
			mapData.ghosts.push_back(ghost);
		}


		return mapData;
	}

	GLuint Loader::readTexture(const char* filename)
	{
		GLuint tex;
		glActiveTexture(GL_TEXTURE0);

		std::vector<unsigned char> image;
		unsigned width, height;

		unsigned error = lodepng::decode(image, width, height, filename);

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return tex;
	}

}
