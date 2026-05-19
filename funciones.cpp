#include "funciones.h"

void initGame(int**& gameMap, const int& length_side) {
    //Paso_1: Como primer paso, creamos las 20 filas y las 20 columnas
    gameMap = new int*[length_side];
        
    for (int i = 0; i<length_side; i++) {
        gameMap[i] = new int[length_side];
    }

    //Paso_2: Como el numero 0 representa espacios vacios, llenamos todo el mapa con ceros
    for (int i = 0; i < length_side; i++) {
        for (int j = 0; j < length_side; j++) {
            gameMap[i][j] = 0;
        }
    }

    //Paso_3: Colocamos el inicio y el final del camino
    gameMap[0][0] = 2; // El numero 2 representa el "I"
    gameMap[19][19] = 3; // El numero 3 representa la "B"

    //Dibujamos el camino por donde pasaran los enemigos. Lo voy a dividir en tramos. El numero 1 representa un espacio negro o lleno
    gameMap[1][0] = 1;
    for (int i = 1; i <= 3; i++) gameMap[i][1] = 1;   //  Primer tramo
    for (int j = 1; j <= 11; j++) gameMap[4][j] = 1;  //  Segundo tramo
    for (int i = 5; i <= 8; i++) gameMap[i][11] = 1;  //  Tercer tramo
    for (int j = 2; j <= 11; j++) gameMap[9][j] = 1;  //  Cuarto tramo
    for (int i = 10; i <= 13; i++) gameMap[i][2] = 1; //  Quinto tramo
    for (int j = 2; j <= 17; j++) gameMap[14][j] = 1; //  Sexto tramo
    for (int i = 15; i <= 19; i++) gameMap[i][17] = 1; // Septimo tramo
    gameMap[19][18] = 1;    

    cout << "----------Mapa creado----------" << endl;
        
    
}
void drawMap() {}
void placeTower(int x, int y) {
    
}
void spawnEnemies() {}
void moveEnemies() {}
void attackEnemies() {}
void verifyResult() {}
void gameStatus() {}

void deleteMap(int**& gameMap, const int& length_side) {
    for (int i = 0; i < length_side; i++) {
        delete[] gameMap[i];
    }

    delete[] gameMap;
    gameMap = nullptr;
}
