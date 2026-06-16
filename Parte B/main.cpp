#include <iostream>
#include <string>

// Ir eliminando los siguientes headers conforme vayan siendo accedidos desde otros de los headers
#include "Game.h"
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include "Camera.h"

using namespace std;

// Definimos el nuevo tamanio del lado del tablero
const int length_side = 40;

// Definimos el costo por torre y la recompensa por enemigo eliminado
const int towerCost = 100;
const int rewardPerEnemy = 50;

int main() {
    // Declaramos el mapa 40 x 40 y la cantidad inicial de dinero
    int** gameMap = nullptr;
    int money = 300;

    // Declaramos la variable que almacenara el comando introducido por el usuario
    string command = "";

    // Implementamos un bucle para el comando init
    do {
        cout << "$: ";
        cin >> command;
    } while (command != "init");


    /// Creacion e importacion de todos los objetos necesarios para el funcionamiento del juego
    ////////////////////////////////////
    ////
    // Motrar automaticamente la ventana visible inicial por medio de una funcion o una clase
    // drawWindow()

    // La cantidad de posiciones de desplazamiento en el movimiento de la camara
    int n = 0;

    // Las coordenadas de la nueva torre construida por placeTower(x, y)
    int x = 0, y = 0;

    // Seran modificados por verifyResult()
    bool victory = false, defeat = false;

    // Inicializamos el objeto game, objeto mapa (arreglo dinamico 40 x 40) y objeto camara
    initGame();

    cout << "Welcome to the world of tower defense xyz\n";
    gameStatus();

    do {
        cout << "$: ";
        cin >> command;

        if (command == "map") {
            // Muestra parte del mapa visible (puede ser metodo del objeto camara)
            drawWindow();
        } else if (command == "up") {
            cin >> n;
            // Metodo del objeto camara
        } else if (command == "down") {
            cin >> n;
            // Metodo del objeto camara
        }  else if (command == "left") {
            cin >> n;
            // Metodo del objeto camara
        } else if (command == "right") {
            cin >> n;
            // Metodo del objeto camara
        } else if (command == "status") {
            gameStatus();
        } else if (command == "place") {
            cin >> x >> y;
            placeTower();
        } else if (command == "wave") {
            // creacion de objetos enemigo
            gameStatus();
        } else if (command == "next") {
            moveEnemies();
            attackEnemies();

            verifyResult();
        } else if (command == "save") {
            // Guardar el estado de juego en un .txt contenido en esta misma carpeta "Parte B"
            saveGame();
        } else if (command == "load") {
            // Restaurar el estado de juego desde un .txt contenido en esta misma carpeta "Parte B"
            loadGame();
        } else if (command == "exit") {
            cout << "El juego ha finalizado\n";
            break;
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
    // deleteMap(gameMap, length_side);

    return 0;
}