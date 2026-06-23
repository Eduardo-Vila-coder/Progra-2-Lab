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

    mapa = new Map(); //mapa 40 x 40
    camara = new Camera(20, 20, 40, 40);

    enemies = new Enemy*[MAX_ENEMIES]; //arreglo de 6 punteros a Enemy
    towers = new Tower*[MAX_TOWERS]; //arreglo de 6 punteros a Tower
    enemyPathIndex = new int[MAX_ENEMIES]; //paraa guardar el indice del camnino

    //inicalizamos tds los punteros a nullptr(es para saber q estan vacios)
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = nullptr;
        enemyPathIndex[i] = 0;
    }
    for (int i = 0; i < MAX_TOWERS; i++) {
        towers[i] = nullptr;
    }

    buildPath(); //aqui construimos el camino ques seguiran los enemigos(I a B)
}

Game::~Game() {
    //aqui borramos cada enemigo que se creo con new
    for (int i = 0; i < MAX_ENEMIES; i++) {
        delete enemies[i]; // si es nullptr, no hace nd
    }
    delete[] enemies; //liberamos el arreglo de punteros

    //se hace lo mismo con las torres
    for (int i = 0; i < MAX_TOWERS; i++) {
        delete towers[i];
    }
    delete[] towers;

    delete[] enemyPathIndex;

    for (int i = 0; i < pathLength; i++) {
        delete[] caminoPath[i];
    }
    delete[] caminoPath;

    delete mapa; //borramos el mapa y camara
    delete camara;
}

void Game::buildPath() {
    pathLength = 118; // numero total de pasos 
    caminoPath = new int*[pathLength];
    for (int i = 0; i < pathLength; i++) {
        caminoPath[i] = new int[2];
    }

    int idx = 0; //el indice que usamos para ir llenando cada posicion

    for (int j = 0; j <= 3; j++) {
        caminoPath[idx][0] = 1;
        caminoPath[idx][1] = j;
        idx++;
    }

    for (int i = 2; i <= 8; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 3;
        idx++;
    }

    for (int j = 4; j <= 24; j++) {
        caminoPath[idx][0] = 8;
        caminoPath[idx][1] = j;
        idx++;
    }

    for (int i = 9; i <= 17; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 24;
        idx++;
    }

    for (int j = 23; j >= 4; j--) {
        caminoPath[idx][0] = 17;
        caminoPath[idx][1] = j;
        idx++;
    }

    for (int i = 18; i <= 26; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 4;
        idx++;
    }

    for (int j = 5; j <= 36; j++) {
        caminoPath[idx][0] = 26;
        caminoPath[idx][1] = j;
        idx++;
    }

    for (int i = 27; i <= 39; i++) {
        caminoPath[idx][0] = i;
        caminoPath[idx][1] = 36;
        idx++;
    }

    for (int j = 37; j <= 39; j++) {
        caminoPath[idx][0] = 39;
        caminoPath[idx][1] = j;
        idx++;
    }
}

void Game::drawWindow() {
    //arreglos para guardar la posición de cada torre/enemigo
    int posiTorres[6][2] = {};
    int posiEnemies[6][2] = {};
    //arreglos para saber si estan activos cada torre/enemigo
    bool torresActiv[6] = {};
    bool enemigosActiv[6] = {};

    for (int i = 0; i < MAX_TOWERS; i++) { //se recorren tds las torres
        if (towers[i] != nullptr) {
            posiTorres[i][0] = towers[i]->getRow();
            posiTorres[i][1] = towers[i]->getCol();
            torresActiv[i] = true;
        }
    }
// recorre tds los enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr && enemies[i]->getActivo()) {
            posiEnemies[i][0] = enemies[i]->getFila();
            posiEnemies[i][1] = enemies[i]->getColumna();
            enemigosActiv[i] = true;
        }
    }

    //la camara muestra el mapa con esos datos
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
    //las coordenadas 1..40 a indices 0..39
    int row = x - 1;
    int col = y - 1;

    //verifica si la posicion esta dentro del mapa
    if (row < 0 || row >= 40 || col < 0 || col >= 40) {
        cout << "Posicion invalida" << endl;
        return;
    }

    //validacion:que no sea camino
    int** mapaGrid = mapa->getGameMap();
    if (mapaGrid[row][col] != 0) {
        cout << "Posicion invalida" << endl;
        return;
    }

    //verifica que no haya otra torre en esa misma posicion
    for (int i = 0; i < numTowers; i++) {
        if (towers[i] != nullptr && towers[i]->getRow() == row && towers[i]->getCol() == col) {
            cout << "Posicion invalida" << endl;
            return;
        }
    }

    //dinero suficiente?
    if (money < TOWER_COST) {
        cout << "Dinero insuficiente" << endl;
        return;
    }

    //no se puede tener mas de 6 torres
    if (numTowers >= MAX_TOWERS) {
        cout << "Maximo de torres alcanzado" << endl;
        return;
    }

    towers[numTowers] = new Tower(row, col, 1, 1);//aqui se creo la torre con new y se guardo
    numTowers++;
    money -= TOWER_COST;

    cout << "Torre colocada" << endl;
    cout << "Dinero: " << money << endl;
}
//lanza la oleada de enemigos
void Game::spawnEnemies() {
    //solo se puede lanzar una oleada por partida
    if (waveSpawned) {
        cout << "Ya se genero una oleada" << endl;
        return;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = new Enemy(1, caminoPath[i][0], caminoPath[i][1]);
        enemyPathIndex[i] = i;
    }

    numEnemies = MAX_ENEMIES;
    waveSpawned = true; //la oleada ya fue lanzada
}

//mueve a cada enemigo un paso adelante
void Game::moveEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] == nullptr || !enemies[i]->getActivo()) continue;

        //avanza una posicion
        enemyPathIndex[i]++;

        // Si ya pasó el último paso (índice >= pathLength), llegó a B
        if (enemyPathIndex[i] >= pathLength) {
            enemies[i]->setActivo(false);//lo desactivamos
            defeat = true; //perdemos
        } else {
            //se actualiza su fil y col segun la nueva posicion del camino
            enemies[i]->setPosicionEnemy(
                caminoPath[enemyPathIndex[i]][0],
                caminoPath[enemyPathIndex[i]][1]
            );
            //ademas tmb hay derrota si el enemigo llega justo al ultimo paso
            if (enemyPathIndex[i] == pathLength - 1) {
                defeat = true;
            }
        }
    }
}

void Game::attackEnemies() {
    // Aquí están las 12 posiciones alrededor de la torre donde puede atacar
    int offsets[12][2] = {
        {0, -2}, {0, 2}, {-2, 0}, {2, 0},
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2},
        {-2, -1}, {2, -1}, {-2, 1}, {2, 1}
    };

    //aqui se recorren tds las torres activas
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

            //verifica si el enemigo esta en alguna de las 12 casillas
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

        //si encontramos un enemigo para atacar
        if (bestEnemy >= 0) {
            //le restamosvida
            enemies[bestEnemy]->enemigo_en_ataque(enemies[bestEnemy]->getSalud());
            towers[t]->newShots(); //la torre dispara
            money += ENEMY_REWARD; //ganamis dinero por matarlo
        }
    }
}

void Game::verifyResult() {
    if (defeat) return; //si ya hemos  perdido , ya no se hace nd
    if (!waveSpawned) return; //si no ha salido la oleada tmp

    bool allDead = true;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr && enemies[i]->getActivo()) {
            allDead = false;
            break;
        }
    }

    if (allDead) {
        victory = true; //ganamosss
    }
}

void Game::saveGame() {
    ofstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "Error al guardar" << endl;
        return;
    }

    //escribir el dinero
    file << money << endl;
    file << numTowers << endl;
    for (int i = 0; i < numTowers; i++) {
        ////guardar las torres
        file << towers[i]->getRow() << " "
             << towers[i]->getCol() << " "
             << towers[i]->getDamage() << " "
             << towers[i]->getShots() << " "
             << towers[i]->getTowersActivate() << endl;
    }

    //guardar laos enemigos
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

    //guarda la posicion de camara
    file << camara->obtenX() << " " << camara->obtenY() << endl;
    file << waveSpawned << endl;

    file.close();
    cout << "Juego guardado" << endl;
}

//Carga la partida desde "savegame.txt"
void Game::loadGame() {
    ifstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "operacion no valida" << endl;
        return;
    }

    // Limpia los arreglos actuales
    for (int i = 0; i < MAX_ENEMIES; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    for (int i = 0; i < MAX_TOWERS; i++) {
        delete towers[i];
        towers[i] = nullptr;
    }

    //leemos el dinero y torres
    file >> money;
    file >> numTowers;
    for (int i = 0; i < numTowers; i++) {
        int r, c, dmg, sh;
        bool act;
        file >> r >> c >> dmg >> sh >> act;
        towers[i] = new Tower(r, c, dmg, sh);
        towers[i]->setTowersActivate(act);
    }

    //leemos enemigos
    file >> numEnemies;
    for (int i = 0; i < numEnemies; i++) {
        int hp, r, c, pIdx;
        bool act;
        file >> hp >> r >> c >> act >> pIdx;
        enemies[i] = new Enemy(hp, r, c);
        enemies[i]->setActivo(act);
        enemyPathIndex[i] = pIdx;
    }

    // Leemos la posición de la cámara y la fijamos
    int camX, camY;
    file >> camX >> camY;
    camara->fijarPosicion(camX, camY);

    // Leemos si la oleada fue lanzada (0 o 1)
    int ws;
    file >> ws;
    waveSpawned = (ws == 1);

    file.close();

    // aqui se reinician las banderas de victria/derrrota, si esq estaban en true
    victory = false;
    defeat = false;

    //mensaje de bienvenida y el estado actual
    cout << "Welcome to the world of tower defense xyz" << endl;
    gameStatus();
    drawWindow();
}

//mueve la camara en una direccion
void Game::moveCamera(int dx, int dy) {
    camara->mover(dx, dy);
}

//para consuktar si ganamos o perdimo
bool Game::isVictory() const {
    return victory;
}

bool Game::isDefeat() const {
    return defeat;
}