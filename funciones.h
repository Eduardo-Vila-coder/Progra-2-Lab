#ifndef PROGRA_2_LAB_FUNCIONES_H
#define PROGRA_2_LAB_FUNCIONES_H

#endif //PROGRA_2_LAB_FUNCIONES_H

void initGame(int**& gameMap, const int& length_side, int towersPosition[6][2], bool towersActivate[6]);
void drawMap(int** gameMap, const int length_side, int towersPosition[6][2], int enemiesPosition[6][2], bool towersActivate[6], bool enemiesActivate[6]);
void placeTower(int x, int y, int &money, int ** gameMap, int towersPosition[6][2], bool towersActivate[6], int towerCost);
void spawnEnemies(int enemiesPosition[6][2], bool enemiesActivate[6]);
void moveEnemies(int enemiesPosition[6][2], const bool enemiesActivate[6], int**& gameMap);
void attackEnemies(int** gameMap, int &money, int enemiesPosition[6][2], bool enemiesActivate[6], int towersPosition[6][2], bool towersActivate[6]);
void verifyResult();
void gameStatus();
void deleteMap(int**& gameMap, const int& length_side);


#ifndef FUNCIONES_H
#define FUNCIONES_H

int verifyResult(int* posicEnemys, bool* vivoEnemys, int numEnemys, int posicBase, bool attack_Iniciado);

void gameStatus(int dinero, int torresColocadas, bool* vivoEnemys, int numEnemys);

#endif
