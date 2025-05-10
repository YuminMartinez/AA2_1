#include "Game.h"
#include <Windows.h> 



void Game::PlayerInPut()
{
    int x = m_player.m_PosX;
    int y = m_player.m_PosY;

    // se mueve hacia delante
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && y > 0)
    {
        if (m_map.m_Type[x][y - 1] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveLeft(); // Asumes que esto actualiza x
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_LEFT;
        }
    }// se mueve hacia izquierda
    else if (GetAsyncKeyState(VK_UP) & 0x8000 && y > 0)
    {
        if (m_map.m_Type[x - 1][y] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveForward();
             // Asumes que esto actualiza y
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
        }
        else if (m_map.m_Type[x - 1][y] == objectType::NPC)
        {
            //codigo hacer parar al npc



            //codigo jugador
            if (GetAsyncKeyState(VK_UP) & 0x8000)
            {

            }
        }
    }// se mueve hacia atras
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && x < m_map.getFilas() - 1)
    {
        if (m_map.m_Type[x][y + 1] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveRight();
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_RIGHT;
        }

    }// se mueve hacia derecha
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && y < m_map.getColumnas() - 1)
    {
        if (m_map.m_Type[x + 1][y] == objectType::DEFAULT)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveBack();           
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_DOWN;
        }
    }
    else
    {
        m_player.m_PosX = x;
        m_player.m_PosY = y;
    }



}


void Game ::printMap() const {
   
   /// Calcular la posición de inicio para la vista
    int startFila = m_player.m_PosX - m_player.playerView_Heigh / 2;  // Filas (Y)
    int startCol = m_player.m_PosY - m_player.playerView_Width / 2;   // Columnas (X)

    // Corregir los límites: asegurarnos de que la vista no se sale del mapa
    if (startFila < 0) startFila = 0;
    if (startCol < 0)  startCol = 0;

    // Asegurarnos de que la vista no se salga del mapa
    if (startFila + m_player.playerView_Heigh > m_map.getFilas()) {
        startFila = m_map.getFilas() - m_player.playerView_Heigh;
    }

    if (startCol + m_player.playerView_Width > m_map.getColumnas()) {
        startCol = m_map.getColumnas() - m_player.playerView_Width;
    }

    // Dibujar el mapa centrado en el jugador
    for (int fila = 0; fila < m_player.playerView_Heigh; ++fila) {
        for (int col = 0; col < m_player.playerView_Width; ++col) {
            int mapY = startFila + fila; // Fila real en el mapa
            int mapX = startCol + col;   // Columna real en el mapa

            if (mapY >= 0 && mapY < m_map.getFilas() &&
                mapX >= 0 && mapX < m_map.getColumnas()) {

                // Marcar al jugador con un símbolo especial (@)
                if (mapY == m_player.m_PosX && mapX == m_player.m_PosY) {
                    switch (m_map.m_Type[mapY][mapX]) {
                    case objectType::PLAYER_UP:    std::cout << "^"; break;
                    case objectType::PLAYER_DOWN:  std::cout << "v"; break;
                    case objectType::PLAYER_LEFT:  std::cout << "<"; break;
                    case objectType::PLAYER_RIGHT: std::cout << ">"; break;
                    }
                }
                else {
                    // Renderizar según el tipo de objeto en esa posición
                    switch (m_map.m_Type[mapY][mapX]) {
                    case objectType::LIMIT:        std::cout << "X"; break;
                       
                    case objectType::NPC:          std::cout << "P"; break;
                    case objectType::MONEY:        std::cout << "$"; break;
                    case objectType::CAR:          std::cout << "C"; break;
                    case objectType::DEFAULT:      std::cout << " "; break;
                    default:                       std::cout << "?"; break;
                    }
                }
            }
        }
        std::cout << '\n';  // Nueva línea por cada fila del mapa
    }

    // Imprimir información de depuración
    std::cout << "\nJugador: (" << m_player.m_PosX << ", " << m_player.m_PosY << ")";
    std::cout << "\nVista: " << m_player.playerView_Width << "x" << m_player.playerView_Heigh;
    std::cout << "\nMapa: " << m_map.getColumnas() << "x" << m_map.getFilas() << "\n";
    
    //visualizacion del mapa entero
    /*
    for (int i = 0; i < m_map.getFilas(); ++i) {
        for (int j = 0; j < m_map.getColumnas(); ++j) {
            switch (m_map.m_Type[i][j]) {
            case objectType::LIMIT: std::cout << "X"; break;
            case objectType::PLAYER_UP: std::cout << "^"; break;
            case objectType::PLAYER_DOWN: std::cout << "v"; break;
            case objectType::PLAYER_LEFT: std::cout << "<"; break;
            case objectType::PLAYER_RIGHT: std::cout << ">"; break;
            case objectType::NPC: std::cout << "P"; break;
            case objectType::MONEY: std::cout << "$"; break;
            case objectType::CAR: std::cout << "C"; break;
            case objectType::DEFAULT: std::cout << " "; break;
            default: std::cout << "?"; break;
            }
        }
        std::cout << '\n';
    }
    */




}



void Game::setPlayer()
{
   
    m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
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