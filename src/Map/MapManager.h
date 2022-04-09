
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <vector>

#include "TileFloor.h"
#include "TileWall.h"

namespace Map {

	using namespace std;

	class MapManager {
		public:
			int sizeX;
			int sizeZ;

			std::vector<Map::TileFloor> floors;
			std::vector<Map::TileWall> walls;

			MapManager();
			virtual ~MapManager();
			
	};

}


#endif