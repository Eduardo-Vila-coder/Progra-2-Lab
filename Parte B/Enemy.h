//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_ENEMY_H
#define PARTE_B_ENEMY_H


class Enemy {
private:
  int salud;
  bool activo;
  int fila;
  int columna;

public:
  Enemy();
  Enemy(int salud, int fila, int columna);  // No escribi int activo porque todo enemigo nace vivo, osea activo == true

  int getSalud() const;
  bool getActivo() const;
  int getFila() const;
  int getColumna() const;

  void setSalud(int salud);
  void setActivo(bool activo);
  void setPosicionEnemy(int fila, int columna);

  bool operator==(const Enemy& otroEnemigo) const;
};


#endif //PARTE_B_ENEMY_H
