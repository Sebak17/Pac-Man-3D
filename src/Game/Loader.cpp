#include "Loader.h"

namespace Game {

	Loader::Loader(Map::MapManager& mapManager): mapManager(mapManager)
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

		auto mapDataInfo = gameData.find("map");
		
		mapManager.sizeX = std::stoi(mapDataInfo.value()["size"]["x"].dump());
		mapManager.sizeZ = std::stoi(mapDataInfo.value()["size"]["z"].dump());


		// ---------------------------[ WALLS ]--------------------------
		for (const auto& mapWall : mapDataInfo.value()["walls"].items())
		{
			float mapWallPosX = std::stof(mapWall.value()["x"].dump());
			float mapWallPosZ = std::stof(mapWall.value()["z"].dump());

			string mapWallDir = mapWall.value()["direction"].dump();
			Map::WallDirection wallDirection;

			if (strcmp(mapWallDir.c_str(), "\"east\"") == 0) {
				wallDirection = Map::WallDirection::EAST;
			}
			else if (strcmp(mapWallDir.c_str(), "\"south\"") == 0) {
				wallDirection = Map::WallDirection::SOUTH;
			}
			else if (strcmp(mapWallDir.c_str(), "\"west\"") == 0) {
				wallDirection = Map::WallDirection::WEST;
			}
			else {
				wallDirection = Map::WallDirection::NORTH;
			}

			Map::TileWall wall(textureWall, glm::vec3(mapWallPosX * 2.0f, 0.0f, mapWallPosZ * 2.0f), wallDirection);
			mapManager.walls.push_back(wall);


			if (wallDirection == Map::WallDirection::NORTH) {
				Map::TileWall wall2(textureWall, glm::vec3((mapWallPosX + 1) * 2.0f, 0.0f, mapWallPosZ * 2.0f), Map::WallDirection::SOUTH);
				mapManager.walls.push_back(wall2);
			}
			else if (wallDirection == Map::WallDirection::EAST) {
				Map::TileWall wall2(textureWall, glm::vec3(mapWallPosX * 2.0f, 0.0f, (mapWallPosZ + 1) * 2.0f), Map::WallDirection::WEST);
				mapManager.walls.push_back(wall2);
			}
			else if (wallDirection == Map::WallDirection::SOUTH) {
				Map::TileWall wall2(textureWall, glm::vec3((mapWallPosX - 1) * 2.0f, 0.0f, mapWallPosZ * 2.0f), Map::WallDirection::NORTH);
				mapManager.walls.push_back(wall2);
			}
			else if (wallDirection == Map::WallDirection::WEST) {
				Map::TileWall wall2(textureWall, glm::vec3(mapWallPosX * 2.0f, 0.0f, (mapWallPosZ - 1) * 2.0f), Map::WallDirection::EAST);
				mapManager.walls.push_back(wall2);
			}

		}
		// --------------------------------------------------------------
		

		// -------------------------[ AUTO MAP ]-------------------------
		for (int x = 0; x < mapManager.sizeX; x++) {
			for (int z = 0; z < mapManager.sizeZ; z++) {
				Map::TileFloor floor(textureFloor, glm::vec3(x * 2.0f, 0.0f, z * 2.0f));
				mapManager.floors.push_back(floor);

				/*
				Map::TileFloor ceiling(textureFloor, glm::vec3(x * 2.0f, 2.0f, z * 2.0f));
				mapManager.floors.push_back(ceiling);
				*/
			}
		}

		for (int x = 0; x < mapManager.sizeX; x++) {
			Map::TileWall wallW(textureWall, glm::vec3(x * 2.0f, 0.0f, 0.0f), Map::WallDirection::WEST);
			mapManager.walls.push_back(wallW);

			Map::TileWall wallE(textureWall, glm::vec3(x * 2.0f, 0.0f, (mapManager.sizeZ - 1) * 2.0f), Map::WallDirection::EAST);
			mapManager.walls.push_back(wallE);
		}


		for (int z = 0; z < mapManager.sizeZ; z++) {
			Map::TileWall wallN(textureWall, glm::vec3((mapManager.sizeX - 1) * 2.0f, 0.0f, z * 2.0f), Map::WallDirection::NORTH);
			mapManager.walls.push_back(wallN);

			Map::TileWall wallS(textureWall, glm::vec3(0, 0.0f, z * 2.0f), Map::WallDirection::SOUTH);
			mapManager.walls.push_back(wallS);
		}
		// --------------------------------------------------------------


		// --------------------------[ GHOSTS ]--------------------------
		auto ghostsElements = gameData.find("ghosts");

		for (const auto& ghostElement : ghostsElements.value().items())
		{
			float ghostPosX = std::stof(ghostElement.value()["position"]["x"].dump());
			float ghostPosZ = std::stof(ghostElement.value()["position"]["z"].dump());

			Entity::Ghost ghost(glm::vec3(ghostPosX * 2.0f, 0.0f, ghostPosZ * 2.0f), mapManager);
			mapData.ghosts.push_back(ghost);
		}
		// --------------------------------------------------------------

		// ---------------------------[ COINS ]--------------------------
		auto coinsElements = gameData.find("coins");

		for (const auto& coinElement : coinsElements.value().items())
		{
			float coinPosX = std::stof(coinElement.value()["position"]["x"].dump());
			float coinPosZ = std::stof(coinElement.value()["position"]["z"].dump());

			Entity::Coin coin(glm::vec3(coinPosX * 2.0f, -0.55f, coinPosZ * 2.0f));
			mapData.coins.push_back(coin);
		}
		// --------------------------------------------------------------


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
