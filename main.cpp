#include "funciones.h"
#include <iostream>
#include <string>

using namespace std;

// Definimos el tamano del lado del tablero
const int length_side = 20;

// Definimos el costo por torre y la recompensa por enemigo eliminado
const int towerCost = 100;
const int rewardPerEnemy = 50;

int main() {
    // Declaramos el mapa 20 x 20 y la cantidad inicial de dinero
    int** gameMap = nullptr;
    int money = 300;

    // Declaramos la variable que almacenara el comando introducido por el usuario
    string command = "";

    // Sera actualizado por spawnEnemies()
    // Cada fila representa un enemigo, y cada columna almacena sus coordenadas (x, y) en ese orden
    // El maximo numero de enemigos posible es 6
    int enemiesPosition[6][2] = {};
    //Creamos un arreglo para verificar si un enemigo esta activo o no
    bool enemiesActivate[6] = {};

    // Sera actualizado por placeTower()
    // Cada fila representa una torre, y cada columna almacena sus coordenadas (x, y) en ese orden
    // Tras los calculos, durante el juego entero, el maximo numero de torres posible es de 6
    int towersPosition[6][2] = {};

    // Cada elemento representa si una torres esta activa o no
    bool towersActivate[6] = {};

    // Las coordenadas de la nueva torre construida por placeTower(x, y)
    int x = 0, y = 0;

    // Seran modificados por verifyResult()
    bool victory = false, defeat = false;

    // Inicializamos el juego y el mapa
    initGame(gameMap, length_side);

    cout << "Welcome to the world of tower defense xyz\n";
    gameStatus();

    do {
        cout << "Comando: ";
        cin >> command;

        if (command == "map") {
            drawMap(gameMap, length_side, towersPosition, enemiesPosition, towersActivate, enemiesActivate);
        } else if (command == "status") {
            gameStatus();
        } else if (command == "place") {
            cin >> x >> y;
            placeTower(x, y, money, gameMap, towersPosition, towersActivate, towerCost);
        } else if (command == "wave") {
            spawnEnemies(enemiesPosition, enemiesActivate);
        } else if (command == "next") {
            moveEnemies();
            attackEnemies();

            verifyResult();
        } else {
            cout << "Not recognized command\n";
        }
    } while (!victory && !defeat);

    if (victory) {
        cout << "GANASTE - Todos los enemigos fueron eliminados\n";
    } else if (defeat) {
        cout << "GAME OVER - La base fue destruida\n";
    }


    // Eliminamos el mapa dinámico creado
    deleteMap(gameMap, length_side);

    return 0;
}