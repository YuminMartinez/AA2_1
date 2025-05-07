#pragma once
#include "util.h"
class Player;
enum class objectType
{
	PLAYER,
	NPC,
	MONEY,
	LIMIT,
	CAR,
	DEFAULT
};
class Map {
private:
    int filas;
    int columnas;
    int limitLosSantos;
    int limitSanFierro;
    Player* m_playerPtr;
    objectType** m_Type;

public:
    Map(Player* player = nullptr); // Constructor con parámetro opcional
    ~Map(); // Destructor para liberar memoria

    void printMap() const;
    
};