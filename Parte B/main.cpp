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
    ///
    // Motrar automaticamente la ventana visible inicial

    return 0;
}