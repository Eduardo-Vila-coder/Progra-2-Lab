#ifndef PARTE_B_GAME_H
#define PARTE_B_GAME_H

#include "Map.h"
#include "Camera.h"

class Game {
private:
    Map mapa;
    Camera camara;

    int money;
    bool waveSpawned;
    bool victory;
    bool defeat;

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
