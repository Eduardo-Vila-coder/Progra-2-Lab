#ifndef PARTE_B_GAME_H
#define PARTE_B_GAME_H

#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tower.h"

class Game {
private:
    Map* mapa;
    Camera* camara;

    Enemy** enemies;
    Tower** towers;
    int* enemyPathIndex;

    int** caminoPath;
    int pathLength;

    int money;
    int numEnemies;
    int numTowers;
    bool waveSpawned;
    bool victory;
    bool defeat;

    static const int MAX_ENEMIES = 6;
    static const int MAX_TOWERS = 6;
    static const int TOWER_COST = 100;
    static const int ENEMY_REWARD = 50;

    void buildPath();

public:
    Game();
    ~Game();

    void drawWindow();
    void gameStatus();
    void placeTower(int x, int y);
    void spawnEnemies();
    void moveEnemies();
    void attackEnemies();
    void verifyResult();
    void saveGame();
    void loadGame();
    void moveCamera(int dx, int dy);

    bool isVictory() const;
    bool isDefeat() const;
};

#endif //PARTE_B_GAME_H
