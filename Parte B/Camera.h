#ifndef PARTE_B_CAMERA_H
#define PARTE_B_CAMERA_H

class Camera {
private:
    int x,y;
    int ancho, alto;
    int limiteAncho;
    int limiteAlto;

public:
    Camera(int ancho_Visor, int alto_Visor, int ancho_Map, int alto_Map);
    ~Camera();

    void mover(int movX, int movY);
    void fijarPosicion(int nuevoX, int nuevoY);

    int obtenX() const;
    int obtenY() const;
    int obtenAncho() const;
    int obtenAlto() const;

    void drawWindow(int** mapa, int posiTorres[6][2], int posiEnemies[6][2], bool torresActiv[6], bool enemiesActiv[6]) const;

    void operator()(int nuevoX, int nuevoY);
};

#endif //PARTE_B_CAMERA_H
