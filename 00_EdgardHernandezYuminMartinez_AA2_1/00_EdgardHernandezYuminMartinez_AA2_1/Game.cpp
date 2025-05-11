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
        else if (m_map.m_Type[x][y - 1] == objectType::MONEY)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveLeft(); // Asumes que esto actualiza x
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_LEFT;
            m_player.money += numRandom(1, m_map.getMaxMoneySantos());
            

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
        else if (m_map.m_Type[x - 1][y] == objectType::MONEY)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveForward();
            // Asumes que esto actualiza y
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
            m_player.money += numRandom(1, m_map.getMaxMoneySantos());
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
        else if (m_map.m_Type[x][y + 1] == objectType::MONEY)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveRight();
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_RIGHT;
            m_player.money += numRandom(1, m_map.getMaxMoneySantos());

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
        else if (m_map.m_Type[x + 1][y] == objectType::MONEY)
        {
            m_map.m_Type[x][y] = objectType::DEFAULT;
            m_player.moveBack();
            m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_DOWN;
            m_player.money += numRandom(1, m_map.getMaxMoneySantos());
        }

    }
    else
    {
        m_player.m_PosX = x;
        m_player.m_PosY = y;
    }
    // Ataque con SPACE (independiente del movimiento)
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) 
    {
        // Coordenadas de las 4 casillas adyacentes (arriba, abajo, izquierda, derecha)
        int adjacent[4][2] = { {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1} };
        // Buscar NPCs adyacentes
        for (int i = 0; i < 4; ++i)
        {
            int targetX = adjacent[i][0];
            int targetY = adjacent[i][1];


            // Verificar si hay un NPC en la posición de ataque
            if (targetX >= 0 && targetX < m_map.getFilas() &&
                targetY >= 0 && targetY < m_map.getColumnas() &&
                m_map.m_Type[targetX][targetY] == objectType::NPC) 
            {
                // 1. Eliminar el NPC del array
                for (int i = 0; i < m_map.getNPC(); i++) 
                {
                    if (m_NPC.npc_PosX[i] == targetX && m_NPC.npc_PosY[i] == targetY) 
                    {
                        m_NPC.npc_Alive[i] = false;
                        break;
                    }
                }
                m_map.m_Type[targetX][targetY] = objectType::MONEY;
            }
        }
    }
}

void Game::printMap() const
{

    /// calcular la posición de inicio para la vista
    int startFila = m_player.m_PosX - m_player.playerView_Heigh / 2;  // Filas (Y)
    int startCol = m_player.m_PosY - m_player.playerView_Width / 2;   // Columnas (X)

    // Corregir los límites: asegurarnos de que la vista no se sale del mapa
    if (startFila < 0) startFila = 0;
    if (startCol < 0)  startCol = 0;

    // Asegurarnos de que la vista no se salga del mapa
    if (startFila + m_player.playerView_Heigh > m_map.getFilas())
    {
        startFila = m_map.getFilas() - m_player.playerView_Heigh;
    }

    if (startCol + m_player.playerView_Width > m_map.getColumnas())
    {
        startCol = m_map.getColumnas() - m_player.playerView_Width;
    }

    // Dibujar el mapa centrado en el jugador
    for (int fila = 0; fila < m_player.playerView_Heigh; ++fila)
    {
        for (int col = 0; col < m_player.playerView_Width; ++col)
        {
            int mapY = startFila + fila; // Fila real en el mapa
            int mapX = startCol + col;   // Columna real en el mapa

            if (mapY >= 0 && mapY < m_map.getFilas() && mapX >= 0 && mapX < m_map.getColumnas())
            {
                // Marcar al jugador con un símbolo especial (@)
                if (mapY == m_player.m_PosX && mapX == m_player.m_PosY)
                {
                    switch (m_map.m_Type[mapY][mapX])
                    {
                    case objectType::PLAYER_UP:
                        std::cout << "^";
                        break;
                    case objectType::PLAYER_DOWN:
                        std::cout << "v";
                        break;
                    case objectType::PLAYER_LEFT:
                        std::cout << "<";
                        break;
                    case objectType::PLAYER_RIGHT:
                        std::cout << ">";
                        break;
                    }
                }
                else
                {
                    // Renderizar según el tipo de objeto en esa posición
                    switch (m_map.m_Type[mapY][mapX])
                    {
                    case objectType::LIMIT:
                        std::cout << "X";
                        break;
                    case objectType::NPC:
                        std::cout << "P";
                        break;
                    case objectType::MONEY:
                        std::cout << "$";
                        break;
                    case objectType::CAR:
                        std::cout << "C";
                        break;
                    case objectType::DEFAULT:
                        std::cout << " ";
                        break;
                    default:
                        std::cout << "?";
                        break;
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
    std::cout << "\nDinero: " << m_player.money << "$";
}

void Game::setPlayer()
{
   
    m_map.m_Type[m_player.m_PosX][m_player.m_PosY] = objectType::PLAYER_UP;
}
void Game::CreateNPC()
{
    for (int i = 0; i < m_map.getNPC(); i++) 
    {
        do 
        {
            m_NPC.npc_PosX[i] = numRandom(1, m_map.getFilas() - 1);
            m_NPC.npc_PosY[i] = numRandom(1, m_map.getLimitLosSantos() - 1);
        } while (m_map.m_Type[m_NPC.npc_PosX[i]][m_NPC.npc_PosY[i]] != objectType::DEFAULT);  // Asegura que solo spawnean en un lugar donde este vacio

        m_map.m_Type[m_NPC.npc_PosX[i]][m_NPC.npc_PosY[i]] = objectType::NPC;
        m_NPC.npc_Alive[i] = true;
    }
}
void Game::NPCMoviment()
{
    for (int p = 0; p < m_map.getNPC(); p++)
    {
        if (m_NPC.npc_Alive[p] == true)
        {
            bool playerInRange[6] = { false };
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int  t = 0;
                    int checkPosX = m_player.m_PosX + i;
                    int checkPosY = m_player.m_PosY + j;
                    while (t < m_map.getNPC())
                    {
                        if (m_NPC.npc_PosX[t] == checkPosX && m_NPC.npc_PosY[t] == checkPosY)
                        {
                            playerInRange[t] = true;
                        }
                        t++;
                    }
                }
            }
            for (int totalNPC = 0; totalNPC < m_map.getNPC(); totalNPC++)
            {
                if (playerInRange[totalNPC] == false)
                {
                    bool moved = false;
                    int intentos = 0;
                    while (!moved && intentos < 10)
                    {
                        int newX = m_NPC.npc_PosX[totalNPC];
                        int newY = m_NPC.npc_PosY[totalNPC];
                        int randomMoviment = numRandom(1, 4);

                        switch (randomMoviment)
                        {
                        case 1: // Arriba
                            newX--;
                            break;
                        case 2: // Abajo
                            newX++;
                            break;
                        case 3: // Izquierda
                            newY--;
                            break;
                        case 4: // Derecha
                            newY++;
                            break;
                        }
                        int limiteX = m_map.getFilas() - 1;
                        int limiteY = m_map.getColumnas() - 1;
                        // Verifica que la posición nueva esté dentro del mapa
                        if (newX >= 0 && newX < limiteX && newY >= 0 && newY < limiteY)
                        {
                            // Verifica que la casilla esté vacía
                            if (m_map.m_Type[newX][newY] == objectType::DEFAULT) 
                            {
                                // Libera la casilla anterior
                                m_map.m_Type[m_NPC.npc_PosX[totalNPC]][m_NPC.npc_PosY[totalNPC]] = objectType::DEFAULT;

                                // Actualiza posición
                                m_NPC.npc_PosX[totalNPC] = newX;
                                m_NPC.npc_PosY[totalNPC] = newY;

                                // Marca la casilla como NPC
                                m_map.m_Type[newX][newY] = objectType::NPC;

                                moved = true;
                            }
                        }
                        intentos++;
                    }
                }
            }
        }
        else
        {
            do 
            {
                m_NPC.npc_PosX[p] = numRandom(1, m_map.getFilas() - 1);
                m_NPC.npc_PosY[p] = numRandom(1, m_map.getLimitLosSantos() - 1);
            } while (m_map.m_Type[m_NPC.npc_PosX[p]][m_NPC.npc_PosY[p]] != objectType::DEFAULT);  // Asegura que solo spawnean en un lugar donde este vacio

            m_map.m_Type[m_NPC.npc_PosX[p]][m_NPC.npc_PosY[p]] = objectType::NPC;
            m_NPC.npc_Alive[p] = true;
        }
    }
}
