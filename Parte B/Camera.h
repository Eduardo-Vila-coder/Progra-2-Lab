#ifndef PARTE_B_CAMERA_H
#define PARTE_B_CAMERA_H

#include <vector>

class Tower;
class Enemy;

class Camera {
private:
    int x, y;
    int ancho, alto;
    int limiteAncho;
    int limiteAlto;

public:
    Camera(int ancho_Visor, int alto_Visor, int ancho_Map, int alto_Map);
    ~Camera();

    void mover(int movX, int movY);
    int obtenX() const;
    int obtenY() const;
    int obtenAncho() const;
    int obtenAlto() const;

    void mostrar(int** mapa, std::vector<Tower*>& torres, std::vector<Enemy*>& enemigos) const;

    void operator()(int nuevoX, int nuevoY);
};

#endif //UNTITLED25_CAMERA_H
