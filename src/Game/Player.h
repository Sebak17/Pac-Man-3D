#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>
#include <ctime>

namespace Game {

	using namespace std;

	class Player {

		public:
			int livesCount;
			int points;

			Player();
			virtual ~Player();

			void setNewGame();

			bool isProtected();
			void addProtection();

		private:
			long long protectionTime;

	};

}

#endif