#include "funciones.h"

void initGame() {}
void drawMap() {}
void placeTower(int x, int y) {}
void spawnEnemies() {}
void moveEnemies() {}
void attackEnemies() {}
void verifyResult() {}
void gameStatus() {}

void deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}