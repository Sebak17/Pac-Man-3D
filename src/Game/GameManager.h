#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

namespace Game {

	using namespace std;

	enum Status {
		MENU,
		PLAYING,
		DEFEAT,
		VICTORY,
	};

	class GameManager {

		public:
			Status status;

			GameManager();
			virtual ~GameManager();

	};

}

#endif