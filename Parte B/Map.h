//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_MAP_H
#define PARTE_B_MAP_H

#include "Enemy.h"
#include "Tower.h"
using namespace std;

class Map {
private:

int** mapa; // Es un arreglo dinamico que representa todo el tablero
int tamanio_lado; // Representa el tamanio del mapa 40 x 40
vector <Enemy*> enemigos; // Guarda punteros a los enemigos de la partida
vector <Tower*> torres; // Guarda punteros a las torres de la partida 

public:
Map()
Map(int tamanio_lado);
~Map();

// Getters
int getTamanioLado() const;
int** getMapa() const;

// El mapa se inicializa con espacios vacios, camino, inicio y base 
void inicializarMapa();

// Esto permite consultar o cambiar una celda del mapa
int getCelda(int fila, int columna) const;
void setCelda(int fila, int columna, int valor);

// Agregacion: Map guarda punteros a objetos creados fuera de Map
void agregarEnemigo(Enemy* enemigo);
void agregarTorre(Tower* torre);

// Devuelven los vectores para que Game pueda recorrer enemigos y torres
vector<Enemy*>& getEnemigos();
vector<Tower*>& getTorres();

// Elimina el arreglo dinamico del mapa void eliminarMapa();
void eliminarMapa();

};


#endif //PARTE_B_MAP_H
