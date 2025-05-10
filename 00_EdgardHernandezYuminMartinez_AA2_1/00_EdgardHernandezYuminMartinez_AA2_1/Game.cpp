#include "Game.h"
#include <Windows.h> 



void Game::PlayerInPut()
{
    int x = m_player.m_PosX;
    int y = m_player.m_PosY;
        
    // se mueve hacia delante
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && y > 0)
    {
        if (m_map.m_Type[x][y-1] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveForward(); // Asumes que esto actualiza x
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
        }
    }// se mueve hacia izquierda
    else if (GetAsyncKeyState(VK_UP) & 0x8000 && y > 0)
    {
        if (m_map.m_Type[x-1][y] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveLeft(); // Asumes que esto actualiza y
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_LEFT;
        }
    }// se mueve hacia atras
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && x < m_map.getFilas() - 1)
    {
        if (m_map.m_Type[x][y+1] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveBack();
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_DOWN;
        }
    }// se mueve hacia derecha
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && y < m_map.getColumnas() - 1)
    {
        if (m_map.m_Type[x+1][y] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveRight();
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_RIGHT;
        }
    }
    else
    {
        m_player.m_PosX = x;
        m_player.m_PosY = y;
    }
}

/*/void Game::npcSpawn(int npc)
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
/*/