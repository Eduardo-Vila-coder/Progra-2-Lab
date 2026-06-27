#include "Cámara.h"
#include "Torre.h"
#include "Enemigo.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Camera::Camera(int ancho_Visor, int alto_Visor, int anchoMap, int altoMap) {
    ancho = ancho_Visor;
    alto = alto_Visor;
    limiteAncho = anchoMap;
    limiteAlto = altoMap;
    x = 0;
    y = 0;
}

Camera::~Camera() {
}

// El operador () sirve para fijar las coordenadas, validando que no sobrepasen los límites del mapa.
// Su definición elimina la necesidad una funcion separada fijarPosicion.
void Camera::operator()(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > limiteAncho - ancho) x = limiteAncho - ancho;
    if (y > limiteAlto - alto) y = limiteAlto - alto;
}

void Camera::mover(int movX, int movY) {
    int nuevoX = x + movX;
    int nuevoY = y + movY;

    // Se usa el operador () en lugar de la funcion fijarPosicion
    (*this)(nuevoX, nuevoY);
}

int Camera::obtenX() const { return x; }
int Camera::obtenY() const { return y; }
int Camera::obtenAncho() const { return ancho; }
int Camera::obtenAlto() const { return alto; }

void Camera::mostrar(int** mapa, vector<Tower*>& torres, vector<Enemy*>& enemigos) const {
    if (mapa == nullptr) return;

    cout << setw(6) << " ";
    for (int j = x; j < x + ancho; j++) {
        cout << setw(4) << j + 1;
    }
    cout << "\n\n";

    for (int i = y; i < y + alto; i++) {
        cout << setw(4) << i + 1 << "  ";

        for (int j = x; j < x + ancho; j++) {
            bool dibujado = false;

            // Saca de manera automatica posiTorres y torresActiv
            for (size_t k = 0; k < torres.size(); k++) {
                if (i == torres.at(k)->getRow() && j == torres.at(k)->getCol() && torres.at(k)->getTowerActivate()) {
                    dibujado = true;
                    cout << setw(4) << ("T" + to_string(k + 1));
                    break;
                }
            }

            // Saca por sí mismo posiEnemies y enemigosActiv
            if (!dibujado) {
                for (size_t k = 0; k < enemigos.size(); k++) {
                    if (i == enemigos.at(k)->getFila() && j == enemigos.at(k)->getColumna() && enemigos.at(k)->getActivo()) {
                        dibujado = true;
                        cout << setw(4) << "E";
                        break;
                    }
                }
            }

            // Texturas estáticas del mapa para renderizar
            if (!dibujado) {
                if (mapa[i][j] == 2) {
                    cout << setw(4) << "I";
                }
                else if (mapa[i][j] == 3) {
                    cout << setw(4) << "B";
                }
                else if (mapa[i][j] == 1) {
                    cout << setw(4) << "*";
                }
                else if (mapa[i][j] == 0) {
                    cout << setw(4) << ".";
                }
            }
        }
        cout << endl;
    }
}

