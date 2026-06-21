//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_ENEMY_H
#define PARTE_B_ENEMY_H


class Enemy {
private:
  int salud;   // Representa la vida del enemigo (Entre 0 y 5)
  bool activo; // Representa el estado del enemigo: true si sigue vivo, false si fue eliminado
  int fila;    // Representa la posicion del enemigo, en este caso, las filas
  int columna; // Representa la posicion del enemigo, en este caso, las columnas 

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

  // Sobrecarga enemigo - puntos de danio
  Enemy operator-(int puntos) const;

  void enemigo_en_ataque(int danio_torre); // Recibe el danio de una torre y actualiza la vida del enemigo

};


#endif //PARTE_B_ENEMY_H
