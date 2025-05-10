#pragma once
#include <iostream>
#include "NPC.h"
#include "Player.h"
#include "Map.h"

class Game
{
public:
	
	Map m_map;
	Player m_player;
	NPC m_NPC;

	bool finish = false;
	void PlayerInPut();
	void setPlayer();
	void printMap() const;
	void CreateNPC();
	void NPCMoviment();
};



