#pragma once
#include "util.h"
class Player
{
public:
	int m_PosX;
	int m_PosY;
	int money = 0;
	Player();
	void moveForward();
	void moveLeft();
	void moveBack();
	void moveRight();

	//void playerMoviment();
};
