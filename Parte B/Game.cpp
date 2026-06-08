#include "Game.h"

void initGame() {}

void gameStatus() {}

void verifyResult() {}

void placeTower() {}

void moveEnemies() {}

void attackEnemies() {}

void saveGame() {}

void loadGame() {}

void deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}