
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

#include "../Map/TileFloor.h"
#include "../Map/TileWall.h"
#include "../Entity/Ghost.h"

namespace Game {

	using namespace std;
	using namespace glm;
	using json = nlohmann::json;

	struct MapData {
		int sizeX;
		int sizeZ;

		std::vector<Map::TileFloor> floors;
		std::vector<Map::TileWall> walls;

		std::vector<Entity::Ghost> ghosts;
	};

	class Loader {
		public:
			Loader();
			virtual ~Loader();

			void loadTextures();
			void destroyTextures();

			Game::MapData loadMap(const char* filename);

			GLuint readTexture(const char* filename);

		private:
			GLuint textureWall, textureFloor;
	};

}

#endif