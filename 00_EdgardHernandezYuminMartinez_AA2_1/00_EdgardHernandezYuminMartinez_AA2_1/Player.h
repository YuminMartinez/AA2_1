#pragma once
#include "util.h"
class Player
{

private:
	int m_PosX;
	int m_PosY;
	int money = 0;
	

public:
	Player();
	int getPosX() const 
	{
		return m_PosX;
	}
	int getPosY() const
	{ 
		return m_PosY; 
	}

	//void playerMoviment();
};
