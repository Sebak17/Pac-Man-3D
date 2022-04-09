
#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "libs/json.hpp"
#include "libs/lodepng.h"

#include "../Map/MapManager.h"

#include "../Map/TileFloor.h"
#include "../Map/TileWall.h"
#include "../Entity/Ghost.h"
#include "../Entity/Coin.h"


namespace Game {

	using namespace std;
	using namespace glm;
	using json = nlohmann::json;

	struct MapData {
		std::vector<Entity::Ghost> ghosts;
		std::vector<Entity::Coin> coins;
	};

	class Loader {
		public:
			Loader(Map::MapManager& mapManager);
			virtual ~Loader();

			void loadTextures();
			void destroyTextures();

			Game::MapData loadMap(const char* filename);

			GLuint readTexture(const char* filename);

		private:
			Map::MapManager& mapManager;

			GLuint textureWall, textureFloor;
	};

}

#endif