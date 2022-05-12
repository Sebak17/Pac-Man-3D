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
		this->livesCount = 3;
		this->points = 0;

		this->protectionTime = 0;
		this->attackModeTime = 0;
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

	bool Player::isAttackMode()
	{
		long long millisec_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return this->attackModeTime >= millisec_now;
	}

	void Player::addAttackMode()
	{
		long long millisec_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		this->attackModeTime = millisec_now + (10 * 1000);
	}

}