#include "Camera.h"
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

void Camera::fijarPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > limiteAncho - ancho) x = limiteAncho - ancho;
    if (y > limiteAlto - alto) y = limiteAlto - alto;
}

void Camera::mover(int movX, int movY) {
    fijarPosicion(x + movX, y + movY);
}

int Camera::obtenX() const { return x; }
int Camera::obtenY() const { return y; }
int Camera::obtenAncho() const { return ancho; }
int Camera::obtenAlto() const { return alto; }

void Camera::mostrar(int** mapa, int posiTorres[6][2], int posiEnemies[6][2], bool torresActiv[6], bool enemigosActiv[6]) const {
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

            if (mapa[i][j] == 2) {
                cout << setw(4) << "I";
                dibujado = true;
            }
            if (mapa[i][j] == 3) {
                cout << setw(4) << "B";
                dibujado = true;
            }

            if (!dibujado) {
                for (int k = 0; k < 6; k++) {
                    if (i == posiTorres[k][0] && j == posiTorres[k][1] && torresActiv[k]) {
                        dibujado = true;
                        cout << setw(4) << ("T" + to_string(k + 1));
                        break;
                    }
                    else if (i == posiEnemies[k][0] && j == posiEnemies[k][1] && enemigosActiv[k]) {
                        dibujado = true;
                        cout << setw(4) << "E";
                        break;
                    }
                }
            }

            if (mapa[i][j] == 1 && !dibujado) {
                cout << setw(4) << "*";
            }
            if (mapa[i][j] == 0 && !dibujado) {
                cout << setw(4) << ".";
            }
        }
        cout << endl;
    }
}

void Camera::operator()(int nuev_X, int nuev_Y) {
    fijarPosicion(nuev_X, nuev_Y);
}

bool Camera::operator==(const Camera& otraCamera) const {
    return (this->x == otraCamera.x && this->y == otraCamera.y);
}
