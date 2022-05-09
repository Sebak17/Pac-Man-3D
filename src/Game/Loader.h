#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "lib/json.hpp"
#include "lib/lodepng.h"

#include "../Map/MapManager.h"

#include "../Map/TileFloor.h"
#include "../Map/TileWall.h"
#include "../Map/Torch.h"
#include "../Entity/Ghost.h"
#include "../Entity/Coin.h"


namespace Game {

	using namespace std;
	using namespace glm;
	using json = nlohmann::json;


	struct MapData {
		glm::vec3 playerStartPos;

		int ghostsAmount;
		std::vector<Entity::Ghost> ghosts;
		int coinsAmount;
		std::vector<Entity::Coin> coins;
	};


	class Loader {

		public:
			GLuint textureLife;

			Loader(Map::MapManager& mapManager);
			virtual ~Loader();

			void loadTextures();
			void destroyTextures();

			Game::MapData loadMap(const char* filename);
			void generateMap(MapData& mapData);

			GLuint readTexture(const char* filename);

		private:
			Map::MapManager& mapManager;

			GLuint textureWall, textureFloor, textureTorch;

			Map::WallDirection getMapElementDirectionFromName(string name);
	};

}

#endif