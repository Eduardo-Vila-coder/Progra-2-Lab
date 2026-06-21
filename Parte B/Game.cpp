#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Game::Game() {
    money = 300;
    numEnemies = 0;
    numTowers = 0;
    waveSpawned = false;
    victory = false;
    defeat = false;

    mapa = new Map();
    camara = new Camera(20, 20, 40, 40);

    enemies = new Enemy*[MAX_ENEMIES];
    towers = new Tower*[MAX_TOWERS];
    enemyPathIndex = new int[MAX_ENEMIES];

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = nullptr;
        enemyPathIndex[i] = 0;
    }
    for (int i = 0; i < MAX_TOWERS; i++) {
        towers[i] = nullptr;
    }

    buildPath();
}

Game::~Game() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        delete enemies[i];
    }
    delete[] enemies;

    for (int i = 0; i < MAX_TOWERS; i++) {
        delete towers[i];
    }
    delete[] towers;

    delete[] enemyPathIndex;

    for (int i = 0; i < pathLength; i++) {
        delete[] caminoPath[i];
    }
    delete[] caminoPath;

    delete mapa;
    delete camara;
}

void Game::buildPath() {
    pathLength = 118;
    caminoPath = new int*[pathLength];
    for (int i = 0; i < pathLength; i++) {
        caminoPath[i] = new int[2];
    }

    int idx = 0;

    // Segmento 1: fila 1, columnas 0-3 (derecha)
    for (int j = 0; j <= 3; j++) {
        caminoPath[idx][0] = 1;
        caminoPath[idx][1] = j;
        idx++;
    }

    // Segmento 2: columna 3, filas 2-8 (abajo)
    for (int i = 2; i <= 8; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 3;
        idx++;
    }

    // Segmento 3: fila 8, columnas 4-24 (derecha)
    for (int j = 4; j <= 24; j++) {
        caminoPath[idx][0] = 8;
        caminoPath[idx][1] = j;
        idx++;
    }

    // Segmento 4: columna 24, filas 9-17 (abajo)
    for (int i = 9; i <= 17; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 24;
        idx++;
    }

    // Segmento 5: fila 17, columnas 23-4 (izquierda)
    for (int j = 23; j >= 4; j--) {
        caminoPath[idx][0] = 17;
        caminoPath[idx][1] = j;
        idx++;
    }

    // Segmento 6: columna 4, filas 18-26 (abajo)
    for (int i = 18; i <= 26; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 4;
        idx++;
    }

    // Segmento 7: fila 26, columnas 5-36 (derecha)
    for (int j = 5; j <= 36; j++) {
        caminoPath[idx][0] = 26;
        caminoPath[idx][1] = j;
        idx++;
    }

    // Segmento 8: columna 36, filas 27-39 (abajo)
    for (int i = 27; i <= 39; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 36;
        idx++;
    }

    // Segmento 9: fila 39, columnas 37-39 (derecha)
    for (int j = 37; j <= 39; j++) {
        caminoPath[idx][0] = 39;
        caminoPath[idx][1] = j;
        idx++;
    }
}

void Game::drawWindow() {
    int posiTorres[6][2] = {};
    int posiEnemies[6][2] = {};
    bool torresActiv[6] = {};
    bool enemigosActiv[6] = {};

    for (int i = 0; i < MAX_TOWERS; i++) {
        if (towers[i] != nullptr) {
            posiTorres[i][0] = towers[i]->getRow();
            posiTorres[i][1] = towers[i]->getCol();
            torresActiv[i] = true;
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr && enemies[i]->getActivo()) {
            posiEnemies[i][0] = enemies[i]->getFila();
            posiEnemies[i][1] = enemies[i]->getColumna();
            enemigosActiv[i] = true;
        }
    }

    camara->mostrar(mapa->getGameMap(), posiTorres, posiEnemies, torresActiv, enemigosActiv);
}

void Game::gameStatus() {
    int activeEnemies = 0;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr && enemies[i]->getActivo()) {
            activeEnemies++;
        }
    }

    cout << "Dinero: " << money << endl;
    cout << "Torres: " << numTowers << endl;
    cout << "Enemigos: " << activeEnemies << endl;
}

void Game::placeTower(int x, int y) {
    int row = x - 1;
    int col = y - 1;

    if (row < 0 || row >= 40 || col < 0 || col >= 40) {
        cout << "Posicion invalida" << endl;
        return;
    }

    int** mapaGrid = mapa->getGameMap();
    if (mapaGrid[row][col] != 0) {
        cout << "Posicion invalida" << endl;
        return;
    }

    for (int i = 0; i < numTowers; i++) {
        if (towers[i] != nullptr && towers[i]->getRow() == row && towers[i]->getCol() == col) {
            cout << "Posicion invalida" << endl;
            return;
        }
    }

    if (money < TOWER_COST) {
        cout << "Dinero insuficiente" << endl;
        return;
    }

    if (numTowers >= MAX_TOWERS) {
        cout << "Maximo de torres alcanzado" << endl;
        return;
    }

    towers[numTowers] = new Tower(row, col, 1, 1);
    numTowers++;
    money -= TOWER_COST;

    cout << "Torre colocada" << endl;
    cout << "Dinero: " << money << endl;
}

void Game::spawnEnemies() {
    if (waveSpawned) {
        cout << "Ya se genero una oleada" << endl;
        return;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = new Enemy(1, caminoPath[i][0], caminoPath[i][1]);
        enemyPathIndex[i] = i;
    }

    numEnemies = MAX_ENEMIES;
    waveSpawned = true;
}

void Game::moveEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] == nullptr || !enemies[i]->getActivo()) continue;

        enemyPathIndex[i]++;

        if (enemyPathIndex[i] >= pathLength) {
            enemies[i]->setActivo(false);
            defeat = true;
        } else {
            enemies[i]->setPosicionEnemy(
                caminoPath[enemyPathIndex[i]][0],
                caminoPath[enemyPathIndex[i]][1]
            );
            if (enemyPathIndex[i] == pathLength - 1) {
                defeat = true;
            }
        }
    }
}

void Game::attackEnemies() {
    int offsets[12][2] = {
        {0, -2}, {0, 2}, {-2, 0}, {2, 0},
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2},
        {-2, -1}, {2, -1}, {-2, 1}, {2, 1}
    };

    for (int t = 0; t < numTowers; t++) {
        if (towers[t] == nullptr || !towers[t]->getTowersActivate()) continue;

        int tRow = towers[t]->getRow();
        int tCol = towers[t]->getCol();

        int bestEnemy = -1;
        int bestPathIdx = -1;

        for (int e = 0; e < MAX_ENEMIES; e++) {
            if (enemies[e] == nullptr || !enemies[e]->getActivo()) continue;

            int eRow = enemies[e]->getFila();
            int eCol = enemies[e]->getColumna();

            for (int r = 0; r < 12; r++) {
                int checkRow = tRow + offsets[r][0];
                int checkCol = tCol + offsets[r][1];

                if (eRow == checkRow && eCol == checkCol) {
                    if (enemyPathIndex[e] > bestPathIdx) {
                        bestPathIdx = enemyPathIndex[e];
                        bestEnemy = e;
                    }
                    break;
                }
            }
        }

        if (bestEnemy >= 0) {
            enemies[bestEnemy]->enemigo_en_ataque(enemies[bestEnemy]->getSalud());
            towers[t]->newShots();
            money += ENEMY_REWARD;
        }
    }
}

void Game::verifyResult() {
    if (defeat) return;
    if (!waveSpawned) return;

    bool allDead = true;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr && enemies[i]->getActivo()) {
            allDead = false;
            break;
        }
    }

    if (allDead) {
        victory = true;
    }
}

void Game::saveGame() {
    ofstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "Error al guardar" << endl;
        return;
    }

    file << money << endl;
    file << numTowers << endl;
    for (int i = 0; i < numTowers; i++) {
        file << towers[i]->getRow() << " "
             << towers[i]->getCol() << " "
             << towers[i]->getDamage() << " "
             << towers[i]->getShots() << " "
             << towers[i]->getTowersActivate() << endl;
    }

    file << numEnemies << endl;
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i] != nullptr) {
            file << enemies[i]->getSalud() << " "
                 << enemies[i]->getFila() << " "
                 << enemies[i]->getColumna() << " "
                 << enemies[i]->getActivo() << " "
                 << enemyPathIndex[i] << endl;
        }
    }

    file << camara->obtenX() << " " << camara->obtenY() << endl;
    file << waveSpawned << endl;

    file.close();
    cout << "Juego guardado" << endl;
}

void Game::loadGame() {
    ifstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "operacion no valida" << endl;
        return;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    for (int i = 0; i < MAX_TOWERS; i++) {
        delete towers[i];
        towers[i] = nullptr;
    }

    file >> money;
    file >> numTowers;
    for (int i = 0; i < numTowers; i++) {
        int r, c, dmg, sh;
        bool act;
        file >> r >> c >> dmg >> sh >> act;
        towers[i] = new Tower(r, c, dmg, sh);
        towers[i]->setTowersActivate(act);
    }

    file >> numEnemies;
    for (int i = 0; i < numEnemies; i++) {
        int hp, r, c, pIdx;
        bool act;
        file >> hp >> r >> c >> act >> pIdx;
        enemies[i] = new Enemy(hp, r, c);
        enemies[i]->setActivo(act);
        enemyPathIndex[i] = pIdx;
    }

    int camX, camY;
    file >> camX >> camY;
    camara->fijarPosicion(camX, camY);

    int ws;
    file >> ws;
    waveSpawned = (ws == 1);

    file.close();

    victory = false;
    defeat = false;

    cout << "Welcome to the world of tower defense xyz" << endl;
    gameStatus();
    drawWindow();
}

void Game::moveCamera(int dx, int dy) {
    camara->mover(dx, dy);
}

bool Game::isVictory() const {
    return victory;
}

bool Game::isDefeat() const {
    return defeat;
}

