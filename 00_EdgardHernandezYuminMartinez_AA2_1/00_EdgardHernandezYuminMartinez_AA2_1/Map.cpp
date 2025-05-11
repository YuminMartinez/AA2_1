#include "util.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"

Map::Map()
{
    std::ifstream myFile("config.txt");
    if (!myFile.is_open()) 
    {
        std::cerr << "Error al abrir config.txt\n";

    }

    // Leer dimensiones
    std::string line;
    int lineNumber = 0;
    while (std::getline(myFile, line)) 
    {
        std::stringstream ss(line);
        std::string item;

        switch (lineNumber) 
        {
        case 0:
            if (std::getline(ss, item, ';')) filas = std::stoi(item);
            if (std::getline(ss, item, ';')) columnas = std::stoi(item);
            break;
        case 1:
            if (std::getline(ss, item, ';')) totalNpc = std::stoi(item);
            if (std::getline(ss, item, ';')) totalToSanFierro = std::stoi(item);
            if (std::getline(ss, item, ';')) maxMoneySantos = std::stoi(item);
            break;
        default:
            std::cerr << "Línea desconocida en config.txt\n";
        }
        lineNumber++;
    }


    // Calcular límites después de tener columnas
    limitLosSantos = columnas / 3;
    limitSanFierro = limitLosSantos * 2;

    // Inicialización de la matriz
    m_Type = new objectType * [filas];
    for (int i = 0; i < filas; ++i) {
        m_Type[i] = new objectType[columnas];
        for (int j = 0; j < columnas; ++j) {
            // 1. Por defecto, todo es transitable (DEFAULT)
            m_Type[i][j] = objectType::DEFAULT;

            // 2. Todos los bordes son LIMIT 
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1 ||    j == limitLosSantos || j == limitSanFierro) {
                m_Type[i][j] = objectType::LIMIT;
            }

            // 3.Colocar passaje
            if (i == 40 && j == limitLosSantos) {
                m_Type[i][j] = objectType::PEAJE;  
            }
            
            if (i == 10 && j == limitSanFierro)
            {
                m_Type[i][j] = objectType::PEAJE;
            }
        }
    }
}
Map::~Map() 
{
    if (m_Type) 
    {
        for (int i = 0; i < filas; ++i) 
        {
            delete[] m_Type[i];
        }
        delete[] m_Type;
    }
}

