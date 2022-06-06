#include "Loader.h"

namespace Game {

	Loader::Loader(Map::MapManager& mapManager): mapManager(mapManager)
	{
		srand(time(NULL));
	}

	Loader::~Loader()
	{
	}

	void Loader::loadTextures()
	{
		textureWall = this->readTexture("assets/textures/bricks.png");
		textureFloor = this->readTexture("assets/textures/stone-wall.png");
		textureTorch = this->readTexture("assets/textures/torch.png");

		textureLife = this->readTexture("assets/textures/life.png");
		textureShield = this->readTexture("assets/textures/shield.png");
		textureSword = this->readTexture("assets/textures/sword.png");

		textureMenu = this->readTexture("assets/textures/menu.png");
		textureDefeat = this->readTexture("assets/textures/defeat.png");
		textureVictory = this->readTexture("assets/textures/victory.png");
	}

	void Loader::destroyTextures()
	{
		glDeleteTextures(1, &textureWall);
		glDeleteTextures(2, &textureFloor);
		glDeleteTextures(2, &textureTorch);

		glDeleteTextures(3, &textureLife);
		glDeleteTextures(4, &textureShield);
		glDeleteTextures(5, &textureSword);

		glDeleteTextures(6, &textureMenu);
		glDeleteTextures(7, &textureDefeat);
		glDeleteTextures(8, &textureVictory);
	}

	Game::MapData Loader::loadMap(const char* filename)
	{
		struct MapData mapData;

		std::ifstream file(filename);
		json gameData;
		file >> gameData;


		float playerStartPosX = std::stof(gameData.find("player").value()["x"].dump());
		float playerStartPosZ = std::stof(gameData.find("player").value()["z"].dump());

		mapData.playerStartPos = glm::vec3(playerStartPosX * 2.0f, 0.0f, playerStartPosZ * 2.0f);

		auto mapDataInfo = gameData.find("map");
		
		mapManager.sizeX = std::stoi(mapDataInfo.value()["size"]["x"].dump());
		mapManager.sizeZ = std::stoi(mapDataInfo.value()["size"]["z"].dump());


		// ---------------------------[ WALLS ]--------------------------
		for (const auto& mapWall : mapDataInfo.value()["walls"].items())
		{
			float mapWallPosX = std::stof(mapWall.value()["x"].dump());
			float mapWallPosZ = std::stof(mapWall.value()["z"].dump());

			Map::WallDirection wallDirection = this->getMapElementDirectionFromName(mapWall.value()["direction"].dump());

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

				
				Map::TileFloor ceiling(textureFloor, glm::vec3(x * 2.0f, 2.0f, z * 2.0f));
				mapManager.floors.push_back(ceiling);
				
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


		// -------------------------[ TORCHES ]--------------------------
		for (const auto& torchElement : mapDataInfo.value()["torches"].items())
		{
			float torchPosX = std::stof(torchElement.value()["x"].dump());
			float torchPosZ = std::stof(torchElement.value()["z"].dump());
			Map::WallDirection torchDirection = this->getMapElementDirectionFromName(torchElement.value()["direction"].dump());

			Map::Torch torch(textureTorch, glm::vec3(torchPosX * 2.0f, 0.0f, torchPosZ * 2.0f), torchDirection);
			mapManager.torches.push_back(torch);
		}
		// --------------------------------------------------------------


		// --------------------------[ GHOSTS ]--------------------------
		mapData.ghostsAmount = gameData.find("ghosts").value();
		// --------------------------------------------------------------


		// ---------------------------[ COINS ]--------------------------
		mapData.coinsAmount = gameData.find("coins").value();
		// --------------------------------------------------------------

		// ---------------------------[ COINS ]--------------------------
		mapData.specialCoinsAmount = gameData.find("special_coins").value();
		// --------------------------------------------------------------

		this->generateMap(mapData);

		return mapData;
	}

	void Loader::generateMap(MapData& mapData)
	{
		std::vector<glm::vec3> availableSlots;

		for (int x = 0; x < mapManager.sizeX; x++) {
			for (int z = 0; z < mapManager.sizeZ; z++) {
				
				float posX = x * 2.0f;
				float posZ = z * 2.0f;

				if(posX == mapData.playerStartPos.x && posZ == mapData.playerStartPos.z) {
					continue;
				}

				availableSlots.push_back(glm::vec3(posX, 0.0f, posZ));
			}
		}

		for (int i = 0; i < mapData.coinsAmount; i++) {
			glm::vec3 pos = availableSlots[rand() % availableSlots.size()];

			Entity::Coin coin(pos);
			mapData.coins.push_back(coin);

			availableSlots.erase(std::remove(availableSlots.begin(), availableSlots.end(), pos), availableSlots.end());
		}

		for (int i = 0; i < mapData.ghostsAmount; i++) {
			glm::vec3 pos = availableSlots[rand() % availableSlots.size()];

			Entity::Ghost ghost(pos, mapManager);
			mapData.ghosts.push_back(ghost);

			availableSlots.erase(std::remove(availableSlots.begin(), availableSlots.end(), pos), availableSlots.end());
		}

		for (int i = 0; i < mapData.specialCoinsAmount; i++) {
			glm::vec3 pos = availableSlots[rand() % availableSlots.size()];

			Entity::SpecialCoin specialCoin(pos);
			mapData.specialCoins.push_back(specialCoin);

			availableSlots.erase(std::remove(availableSlots.begin(), availableSlots.end(), pos), availableSlots.end());
		}

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


	Map::WallDirection Loader::getMapElementDirectionFromName(string name)
	{
		if (strcmp(name.c_str(), "\"east\"") == 0) {
			return Map::WallDirection::EAST;
		}
		else if (strcmp(name.c_str(), "\"south\"") == 0) {
			return Map::WallDirection::SOUTH;
		}
		else if (strcmp(name.c_str(), "\"west\"") == 0) {
			return Map::WallDirection::WEST;
		}
		else {
			return Map::WallDirection::NORTH;
		}
	}

}
