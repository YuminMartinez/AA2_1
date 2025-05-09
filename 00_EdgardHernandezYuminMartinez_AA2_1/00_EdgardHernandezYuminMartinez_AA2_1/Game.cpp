#include "Game.h"
#include <Windows.h> 

void Game:: CheckLimit(int x,int y)
{
	if (m_map.m_Type[m_player.m_PosX][m_player.m_PosY] == objectType::LIMIT)
	{
		m_player.m_PosX = x;
		m_player.m_PosY = y;
	}
}
void Game::PlayerInPut()
{
	
	m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::DEFAULT;
	int x = m_player.m_PosX;
	int y = m_player.m_PosY;
	

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_player.moveForward();
		m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_LEFT;
		CheckLimit(x, y);

	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_player.moveLeft();
		m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
		CheckLimit(x, y);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_player.moveBack();
		m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_RIGHT;
		CheckLimit(x, y);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_player.moveRight();
		m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_DOWN;
		CheckLimit(x, y);
	}

	
}
void Game::npcSpawn(int npc)
{
	for (int i = 0; i < npc; i++) {
		int randX, randY;
		do {
			randX = rand() % 5;
			randY = rand() % 5;
		} while (m_map.m_Type[randX][randY] != objectType::DEFAULT);  // Asegura que no haya otro enemigo o el jugador

		m_map.m_Type[randX][randY] = objectType::NPC;  // Coloca al enemigo
	

		
	}
}
