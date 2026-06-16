#include "Game.h"

void Game::initGame() {}

void Game::gameStatus() {}

void Game::verifyResult() {}

void Game::placeTower() {}

void Game::moveEnemies() {}

void Game::attackEnemies() {}

void Game::saveGame() {}

void Game::loadGame() {}

void Game::deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}