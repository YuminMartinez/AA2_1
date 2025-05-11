#pragma once
#include "util.h"
class Player;
enum class objectType
{
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    NPC,
    MONEY,
    LIMIT,
    CAR,
    PEAJE,
	DEFAULT
};
class Map {
private:
    int filas;
    int columnas;
    int totalToSanFierro;
    int maxMoneySantos;
    int limitLosSantos;
    int limitSanFierro;
    int totalNpc;
     

public:

    objectType** m_Type;
    Map();
    ~Map();
    
    int getLimitLosSantos() const 
    {
        return limitLosSantos; 
    }
    int getFilas() const 
    { 
        return filas; 
    }
    int getNPC() const 
    { 
        return totalNpc; 
    }
    int getColumnas() const 
    { 
        return columnas; 
    }
    int getMaxMoneySantos() const
    {
        return maxMoneySantos;
    }
    
};