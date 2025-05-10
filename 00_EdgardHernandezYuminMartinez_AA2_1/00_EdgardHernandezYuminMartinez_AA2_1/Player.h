#pragma once
#include "util.h"
class Player
{
public:
	int m_PosX;
	int m_PosY;
	int money = 0;
	int playerView_Width = 11;
	int playerView_Heigh = 7;

	Player();
	void moveForward();
	void moveLeft();
	void moveBack();
	void moveRight();
	
	

	//void playerMoviment();
};
