#include "util.h"


Map::Map(Player* player) :
    m_playerPtr(player),
    filas(0), columnas(0),
    limitLosSantos(0), limitSanFierro(0),
    m_Type(nullptr)
{
    std::ifstream myFile("config.txt");
    if (!myFile.is_open()) {
        std::cerr << "Error al abrir config.txt\n";
        return;
    }

    // Leer dimensiones
    std::string line;
    if (!std::getline(myFile, line)) {
        std::cerr << "Error leyendo config.txt\n";
        return;
    }

    std::stringstream ss(line);
    std::string item;

    if (!std::getline(ss, item, ';') || (filas = std::stoi(item)) <= 0) {
        std::cerr << "Filas inválidas\n";
        return;
    }

    if (!std::getline(ss, item, ';') || (columnas = std::stoi(item)) <= 0) {
        std::cerr << "Columnas inválidas\n";
        return;
    }

    // Calcular límites después de tener columnas
    limitLosSantos = columnas / 3;
    limitSanFierro = limitLosSantos * 2;

    // Inicializar matriz correctamente
    m_Type = new objectType * [filas];
    for (int i = 0; i < filas; ++i) {
        m_Type[i] = new objectType[columnas];
        for (int j = 0; j < columnas; ++j) {
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1 ||
                j == limitLosSantos || j == limitSanFierro) {
                m_Type[i][j] = objectType::LIMIT;
            }
            else {
                m_Type[i][j] = objectType::DEFAULT;
            }
        }


    }

    int x = m_playerPtr->getPosX();
    int y = m_playerPtr->getPosY();
    m_Type[x][y] = objectType::PLAYER;
}

Map::~Map() {
    if (m_Type) {
        for (int i = 0; i < filas; ++i) {
            delete[] m_Type[i];
        }
        delete[] m_Type;
    }
}



void Map::printMap() const {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            switch (m_Type[i][j]) {
            case objectType::LIMIT: std::cout << " X"; break;
            case objectType::PLAYER: std::cout << " P"; break;
            case objectType::DEFAULT: std::cout << "  "; break;
            default: std::cout << " ?";
            }
        }
        std::cout << '\n';
    }
}