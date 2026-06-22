#include "Map.h"

Map::Map() {
    length_side = 40;
    gameMap = nullptr;

    crearMapa();
    crearCamino();
}

Map::Map(int length_side) {
    this->length_side = length_side;
    gameMap = nullptr;

    crearMapa();
    crearCamino();
}

Map::~Map() {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}

void Map::crearMapa() {
    gameMap = new int*[length_side];

    for (int i = 0; i < length_side; i++) {
        gameMap[i] = new int[length_side];

        for (int j = 0; j < length_side; j++) {
            gameMap[i][j] = 0;
        }
    }
}

void Map::crearCamino() {
    // Inicioo: fila 1, columna 1
    gameMap[0][0] = 2;

    // Fila 2: desde columna 1 hasta columna 4
    for (int j = 0; j <= 3; j++) {
        gameMap[1][j] = 1;
    }

    // Columna 4: desde fila 2 hasta fila 9
    for (int i = 1; i <= 8; i++) {
        gameMap[i][3] = 1;
    }

    // Fila 9: desde columna 4 hasta columna 25
    for (int j = 3; j <= 24; j++) {
        gameMap[8][j] = 1;
    }

    // Columna 25: desde fila 9 hasta fila 18
    for (int i = 8; i <= 17; i++) {
        gameMap[i][24] = 1;
    }

    // Fila 18: desde columna 25 hasta columna 5
    for (int j = 4; j <= 24; j++) {
        gameMap[17][j] = 1;
    }

    // Columna 5: desde fila 18 hasta fila 27
    for (int i = 17; i <= 26; i++) {
        gameMap[i][4] = 1;
    }

    // Fila 27: desde columna 5 hasta columna 37
    for (int j = 4; j <= 36; j++) {
        gameMap[26][j] = 1;
    }

    // Columna 37: desde fila 27 hasta fila 40
    for (int i = 26; i <= 39; i++) {
        gameMap[i][36] = 1;
    }

    // Fila 40: desde columna 37 hasta columna 40
    for (int j = 36; j <= 39; j++) {
        gameMap[39][j] = 1;
    }

    // Base: fila 40, columna 40
    gameMap[39][39] = 3;
}

int** Map::getGameMap() const {
    return gameMap;
}

int Map::getLengthSide() const {
    return length_side;
}
