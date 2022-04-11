#include "Player.h"

namespace Game {

	Player::Player()
	{
		this->setNewGame();
	}

	Player::~Player()
	{
	}

	void Player::setNewGame()
	{
		this->livesCount = 100;
		this->points = 0;

		this->protectionTime = 0;
	}

	bool Player::isProtected()
	{
		long long millisec_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return this->protectionTime >= millisec_now;
	}

	void Player::addProtection()
	{
		long long millisec_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		this->protectionTime = millisec_now + (2.5 * 1000);
	}

}