#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Game::Game() : camara(20, 20, 40, 40) {
    money = 300;
    waveSpawned = false;
    victory = false;
    defeat = false;
}

Game::~Game() {
}

void Game::drawWindow() {
    camara.drawWindow(mapa.getGameMap(), mapa.getTorres(), mapa.getEnemigos());
}

void Game::gameStatus() {
    vector<Enemy*>& enemigos = mapa.getEnemigos();

    int activeEnemies = 0;
    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getActivo()) activeEnemies++;
    }

    cout << "Dinero: " << money << endl;
    cout << "Torres: " << mapa.getTorres().size() << endl;
    cout << "Enemigos: " << activeEnemies << endl;
}

void Game::placeTower(int x, int y) {
    mapa.placeTower(x, y, 1, 1, money);
}

void Game::spawnEnemies() {
    if (waveSpawned) {
        cout << "Ya se genero una oleada" << endl;
        return;
    }
    mapa.spawnEnemies();
    waveSpawned = true;
}

void Game::moveEnemies() {
    mapa.moveEnemies();
}

void Game::attackEnemies() {
    mapa.attackEnemies(money);
}

void Game::verifyResult() {
    mapa.verifyResult(victory, defeat);
}

void Game::saveGame() {
    ofstream file("../savegame.txt");
    if (!file.is_open()) {
        cout << "Error al guardar" << endl;
        return;
    }

    file << money << endl;
    file << waveSpawned << endl;
    file << camara.obtenX() << " " << camara.obtenY() << endl;

    vector<Tower*>& torres = mapa.getTorres();
    file << torres.size() << endl;
    for (int i = 0; i < torres.size(); i++) {
        file << torres[i]->getRow() << " "
             << torres[i]->getCol() << " "
             << torres[i]->getDamage() << " "
             << torres[i]->getShots() << " "
             << torres[i]->getTowerActivate() << endl;
    }

    vector<Enemy*>& enemigos = mapa.getEnemigos();
    file << enemigos.size() << endl;
    for (int i = 0; i < enemigos.size(); i++) {
        file << enemigos[i]->getSalud() << " "
             << enemigos[i]->getFila() << " "
             << enemigos[i]->getColumna() << " "
             << enemigos[i]->getActivo() << endl;
    }

    file.close();
    cout << "Juego guardado" << endl;
}

void Game::loadGame() {
    ifstream file("../savegame.txt");
    if (!file.is_open()) {
        cout << "operacion no valida" << endl;
        return;
    }

    // Limpiando completamente el vector enemigos de la partida actual
    vector<Enemy*>& enemigos = mapa.getEnemigos();
    for (int i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
    enemigos.clear();

    // Limpiando completamente el vector torres de la partida actual
    vector<Tower*>& torres = mapa.getTorres();
    for (int i = 0; i < torres.size(); i++) {
        delete torres[i];
    }
    torres.clear();

    file >> money;

    int ws;
    file >> ws;
    waveSpawned = (ws == 1);

    int camX, camY;
    file >> camX >> camY;
    camara.fijarPosicion(camX, camY);

    int numTorres;
    file >> numTorres;
    for (int i = 0; i < numTorres; i++) {
        int r, c, dmg, sh;
        bool act;
        file >> r >> c >> dmg >> sh >> act;
        Tower* t = new Tower(r, c, dmg, sh);
        t->setTowersActivate(act);
        mapa.getTorres().push_back(t);
    }

    int numEnemigos;
    file >> numEnemigos;
    for (int i = 0; i < numEnemigos; i++) {
        int hp, r, c;
        bool act;
        file >> hp >> r >> c >> act;
        Enemy* e = new Enemy(hp, r, c);
        e->setActivo(act);
        mapa.getEnemigos().push_back(e);
    }

    file.close();

    victory = false;
    defeat = false;

    cout << "Welcome to the world of tower defense xyz" << endl;
    gameStatus();
    drawWindow();
}

void Game::moveCamera(int dx, int dy) {
    camara.mover(dx, dy);
}

bool Game::isVictory() const {
    return victory;
}

bool Game::isDefeat() const {
    return defeat;
}
