#ifndef PARTE_B_GAME_H
#define PARTE_B_GAME_H


void initGame();

void gameStatus();

void verifyResult();

void placeTower();

void moveEnemies();

void attackEnemies();

void saveGame();

void loadGame();

void deleteMap(int**& gameMap, const int& length_side);


#endif //PARTE_B_GAME_H