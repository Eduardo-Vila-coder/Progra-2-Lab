#include "Map.h"

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

    // Decimo tramo: fila 40, desde la columna 37 hasta la columna 40
    for (int j = 36; j <= 39; j++) {
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

void Map::placeTower(int fila, int columna, int danio, int disparos) {
    // Validamos que la torre este dentro del mapa
    if (fila < 0 || fila >= length_side || columna < 0 || columna >= length_side) {
        return;
    }

    // Esto es porque no se puede colocar una torre sobre el camino, inicio o base
    if (gameMap[fila][columna] != 0) {
        return;
    }

    // El danio permitido solo es de 1 a 5
    if (danio < 1 || danio > 5) {
        return;
    }

    Tower* nuevaTorre = new Tower(fila, columna, danio, disparos);
    torres.push_back(nuevaTorre);
}

void Map::spawnEnemies() {
    // El enemigo aparece en el inicio del camino es decir en la fila 1, columna 1
    Enemy* nuevoEnemigo = new Enemy(5, 0, 0);
    enemigos.push_back(nuevoEnemigo);
}

void Map::moveEnemies() {
    for (int i = 0; i < enemigos.size(); i++) {
        // Ignoramos a los enemigos eliminados
        if (enemigos[i]->getActivo() == false) {
            continue;
        }

        int fila = enemigos[i]->getFila();
        int columna = enemigos[i]->getColumna();

        // Inicio: fila 1, columna 1 y luego baja a la fila 2
        if (fila == 0 && columna == 0) {
            enemigos[i]->setPosicionEnemy(1, 0);
        }

        // Fila 2: avanza hacia la derecha hasta la columna 4
        else if (fila == 1 && columna < 3) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Columna 4: baja hasta la fila 9
        else if (columna == 3 && fila < 8) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Fila 9: avanza hacia la derecha hasta la columna 25
        else if (fila == 8 && columna < 24) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Columna 25: baja hasta la fila 18
        else if (columna == 24 && fila < 17) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Fila 18: avanza hacia la izquierda hasta la columna 5
        else if (fila == 17 && columna > 4) {
            enemigos[i]->setPosicionEnemy(fila, columna - 1);
        }

        // Columna 5: baja hasta la fila 27
        else if (columna == 4 && fila < 26) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Fila 27: avanza hacia la derecha hasta la columna 37
        else if (fila == 26 && columna < 36) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }

        // Columna 37: baja hasta la fila 40
        else if (columna == 36 && fila < 39) {
            enemigos[i]->setPosicionEnemy(fila + 1, columna);
        }

        // Fila 40: avanza hacia la derecha hasta la base
        else if (fila == 39 && columna < 39) {
            enemigos[i]->setPosicionEnemy(fila, columna + 1);
        }
    }
}

void Map::attackEnemies() {
    for (int i = 0; i < torres.size(); i++) {
        // Ignoramos las torres sin disparos o desactivadas
        if (torres[i]->getTowersActivate() == false) {
            continue;
        }

        for (int j = 0; j < enemigos.size(); j++) {
            // Ignoramos a los enemigos ya estan eliminados
            if (enemigos[j]->getActivo() == false) {
                continue;
            }

            int diferenciaFila = enemigos[j]->getFila() - torres[i]->getRow();
            int diferenciaColumna = enemigos[j]->getColumna() - torres[i]->getCol();

            // Chequeamos si el enemigo esta dentro de uno de los 12 puntos del rango
            for (int rango = 0; rango < 12; rango++) {
                if (diferenciaFila == torres[i]->getFilaRango(rango) && diferenciaColumna == torres[i]->getColumnaRango(rango)) {
                    
                    enemigos[j]->enemigo_en_ataque(torres[i]->getDamage());
                    torres[i]->newShots();

                    // Debemos recordar que una torre dispara solo una vez por turno
                    break;
                }
            }

            // Si la torre ya no tiene disparos, dejamos de buscar enemigos
            if (torres[i]->getTowersActivate() == false) {
                break;
            }
        }
    }
}

void Map::verifyResult(bool& victory, bool& defeat) {
    // Si aun no existen enemigos, entonces todavia no se puede ganar
    if (enemigos.empty()){
        return;
    }

    bool quedaEnemigoVivo = false;

    for (int i = 0; i < enemigos.size(); i++){
        // Si un enemigo vivo llega a la base, entonces se pierde
        if (enemigos[i]->getActivo() && enemigos[i]->getFila() == 39 && enemigos[i]->getColumna() == 39) {
            defeat = true;
            return;
        }

        // Si queda un enemigo vivo, entonces todavia no se gana
        if (enemigos[i]->getActivo()){
            quedaEnemigoVivo = true;
        }     
    }

    // Se gana unicamente cuando hubo enemigos y todos estos enemigos fueron eliminados
    if (quedaEnemigoVivo == false) {
        victory = true;
    }
}
