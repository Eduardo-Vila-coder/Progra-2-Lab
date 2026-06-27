#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


Map::Map() {
    length_side = 40;
    gameMap = nullptr;
    crearMapa();
    crearCamino();
}

Map::Map(int length_side) {
    this->length_side = length_side;
    gameMap = nullptr;
    crearMapa();
    crearCamino();
}

Map::~Map() {
    // Eliminamos los enemigos que hemos creado con new
    for (int i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }

    // Eliminamos las torres que hemos creado con new
    for (int i = 0; i < torres.size(); i++) {
        delete torres[i];
    }

    // Eliminamos el mapa dinamico
    if (gameMap != nullptr) {
        for (int i = 0; i < length_side; i++) {
            delete[] gameMap[i];
        }
        

        delete[] gameMap;
        gameMap = nullptr;
    }
}

void Map::crearMapa() {
    gameMap = new int*[length_side];

    for (int i = 0; i < length_side; i++) {
        gameMap[i] = new int[length_side];

        for (int j = 0; j < length_side; j++) {
            gameMap[i][j] = 0;
        }
    }
    
}

void Map::crearCamino() {
    // Inicio: fila 1, columna 1
    gameMap[0][0] = 2;

    // Primer tramo: baja desde la fila 1 hasta la fila 2
    gameMap[1][0] = 1;

    // Segundo tramo: fila 2, desde la columna 1 hasta la columna 4
    for (int j = 0; j <= 3; j++) {
        gameMap[1][j] = 1;
    }

    // Tercer tramo: columna 4, desde la fila 2 hasta la fila 9
    for (int i = 1; i <= 8; i++) {
        gameMap[i][3] = 1;
    }

    // Cuarto tramo: fila 9, desde la columna 4 hasta la columna 25
    for (int j = 3; j <= 24; j++) {
        gameMap[8][j] = 1;
    }

    // Quinto tramo: columna 25, desde la fila 9 hasta la fila 18
    for (int i = 8; i <= 17; i++) {
        gameMap[i][24] = 1;
    }

    // Sexto tramo: fila 18, desde la columna 25 hasta la columna 5
    for (int j = 24; j >= 4; j--) {
        gameMap[17][j] = 1;
    }

    // Septimo tramo: columna 5, desde la fila 18 hasta la fila 27
    for (int i = 17; i <= 26; i++) {
        gameMap[i][4] = 1;
    }

    // Octavo tramo: fila 27, desde la columna 5 hasta la columna 37
    for (int j = 4; j <= 36; j++) {
        gameMap[26][j] = 1;
    }

    // Noveno tramo: columna 37, desde la fila 27 hasta la fila 40
    for (int i = 26; i <= 39; i++) {
        gameMap[i][36] = 1;
    }

    // Decimo tramo: fila 40, desde la columna 37 hasta la columna 39
    for (int j = 36; j <= 38; j++) {
        gameMap[39][j] = 1;
    }

    // Base: fila 40, columna 40
    gameMap[39][39] = 3;
}

int** Map::getGameMap() const {
    return gameMap;
}

int Map::getLengthSide() const {
    return length_side;
}

void Map::placeTower(int fila, int columna, int danio, int disparos, int& dinero) {
    int costoTorre = 100;
    // El usuario escribe filas y columnas desde 1 hasta 40, entonces restamos 1 porque arreglo usa indices desde 0 hasta 39.
    fila = fila - 1;
    columna = columna - 1;

    if (fila < 0 || fila >= length_side || columna < 0 || columna >= length_side) {
        cout << "Error: la posicion ingresada esta fuera del mapa" << endl;
        return;
    }

    if (danio < 1 || danio > 5) {
        cout << "Error: el danio debe estar entre 1 y 5" << endl;
        return;
    }

    if (disparos <= 0) {
        cout << "Error: la torre debe tener al menos un disparo" << endl;
        return;
    }

    if (dinero < costoTorre) {
        cout << "Error: no tienes dinero suficiente para colocar una torre" << endl;
        return;
    }

    if (gameMap[fila][columna] != 0) {
        cout << "Error: esa posicion no esta disponible" << endl;
        return;
    }

    bool posicionPermitida = false;

    // Primer tramo
    if (fila == 2 && columna >= 0 && columna <= 2) {
        posicionPermitida = true;
    }

    // Segundo tramo
    if (columna == 2 && fila >= 3 && fila <= 8) {
        posicionPermitida = true;
    }

    // Tercer tramo
    if (fila == 9 && columna >= 2 && columna <= 23){
        posicionPermitida = true;
    }

    // Cuarto tramo
    if (columna == 23 && fila >= 10 && fila <= 16){
        posicionPermitida = true;
    }

    // Quinto tramo
    if (fila == 16 && columna >= 3 && columna <= 22) {
        posicionPermitida = true;
    }

    // Sexto tramo
    if (columna == 3 && fila >= 17 && fila <= 27){
        posicionPermitida = true;
    }

    // Septimo tramo
    if (fila == 27 && columna >= 4 && columna <= 35){
        posicionPermitida = true;
    }

    // Octavo tramo
    if (columna == 35 && fila >= 28 && fila <= 39){
        posicionPermitida = true;
    }

    if (posicionPermitida == false) {
        cout << "Error: la torre debe colocarse en una zona permitida" << endl;
        return;
    }

    Tower* nuevaTorre = new Tower(fila, columna, danio, disparos);

    torres.push_back(nuevaTorre);

    gameMap[fila][columna] = 4;

    dinero = dinero - costoTorre;

    cout << "Torre colocada\n";
    cout << "Dinero: " << dinero << endl;
}

void Map::spawnEnemies() {
    int cantidadEnemigos = rand() % 5 + 1;

    // Pasamos los enemigos al vector de la clase y lo hacemos de atras hacia adelante
    for (int i = cantidadEnemigos - 1; i >= 0; i--) {
        Enemy* nuevoEnemigo = new Enemy(1, start_position[i][0], start_position[i][1]);
        enemigos.push_back(nuevoEnemigo);
    }

    cout << cantidadEnemigos << " enemigos aparecieron en el punto de inicio" << endl;
}

void Map::moveEnemies() {
    bool huboAvance = false;

    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getActivo() == false) {
            continue;
        }

        huboAvance = true;

        int fila = enemigos[i]->getFila();
        int columna = enemigos[i]->getColumna();

        // Tramo 1: fila 0, desde columna 1 hasta columna 3
        if (fila == 0 && columna >= 1 && columna <= 3) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Tramo 2: columna 4, desde fila 0 hasta fila 6
        else if (columna == 4 && fila >= 0 && fila <= 6) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Tramo 3: fila 7, desde columna 4 hasta columna 24
        else if (fila == 7 && columna >= 4 && columna <= 24) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Tramo 4: columna 25, desde fila 7 hasta fila 17
        else if (columna == 25 && fila >= 7 && fila <= 17) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Tramo 5: fila 18, desde columna 25 hasta columna 6
        else if (fila == 18 && columna <= 25 && columna >= 6) {
            enemigos[i]->setPosicionEnemy(fila, columna - 1);
        }

        // Tramo 6: columna 5, desde fila 18 hasta fila 24
        else if (columna == 5 && fila >= 18 && fila <= 24) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Tramo 7: fila 25, desde columna 5 hasta columna 36
        else if (fila == 25 && columna >= 5 && columna <= 36) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Tramo 8: columna 37, desde fila 25 hasta fila 37
        else if (columna == 37 && fila >= 25 && fila <= 37) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Tramo 9: 
        else if (fila == 38 && columna == 37) {
            enemigos[i]->setPosicionEnemy(38,38);
        }

        else if (fila == 38 && columna == 38) {
            enemigos[i]->setPosicionEnemy(38, 39);
        }

        // Último movimiento hacia la base
        else if (fila == 38 && columna == 39) {
            enemigos[i]->setPosicionEnemy(39, 39);
            gameMap[19][19] = 0;
        }
    }

    if (huboAvance) {
        cout << "Enemigos avanzaron" << endl;
    }
}

void Map::attackEnemies(int& dinero) {
    int recompensa = 50;
    bool torre_ataco = false;
    bool hubo_ataque = false;

    for (int i = 0; i < torres.size(); i++) {
        if (torres[i]->getTowerActivate() == false) {
            continue;
        }

        torre_ataco = false;
        for (int j = 0; j < enemigos.size(); j++) {
            if (enemigos[j]->getActivo() == false) {
                continue;
            }

            int diferenciaFila = enemigos[j]->getFila() - torres[i]->getRow();
            int diferenciaColumna = enemigos[j]->getColumna() - torres[i]->getCol();

            for (int rango = 0; rango < 12; rango++) {
                if (diferenciaFila == torres[i]->getFilaRango(rango) &&
                    diferenciaColumna == torres[i]->getColumnaRango(rango)) {

                    enemigos[j]->enemigo_en_ataque(torres[i]->getDamage());
                    torres[i]->newShots();
                    torre_ataco = true;
                    hubo_ataque = true;

                    if (enemigos[j]->getActivo() == false) {
                        dinero = dinero + recompensa;
                    }

                    break;
                }
            }

            if (torre_ataco) {
                break;
            }
        }
    }

    if (hubo_ataque) {
        cout << "Torres atacaron\nEstado actualizado\n";
    }
}

 
void Map::verifyResult(bool& victory, bool& defeat) {
    victory = false;
    defeat = false;

    if (enemigos.empty()) {
        return;
    }

    bool quedaEnemigoVivo = false;

    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getActivo() &&
            enemigos[i]->getFila() == 39 &&
            enemigos[i]->getColumna() == 39) {

            defeat = true;
            return;
        }

        if (enemigos[i]->getActivo()) {
            quedaEnemigoVivo = true;
        }
    }

    if (quedaEnemigoVivo == false) {
        victory = true;
    }
}
