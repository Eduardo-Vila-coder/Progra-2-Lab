//
// Created by HP on 6/5/2026.
//

#ifndef PARTE_B_TOWER_H
#define PARTE_B_TOWER_H

//Permita multiples disparos
//Tenga rango de ataque
//Tenga dano configurable (1 - 5)


class Tower {
private:
    int row; //coordenadas de la torre
    int col;
    int attackRange; //rango de ataque
    int damage; //daño causado
    bool towerActivate; //para verificar si la torre está activa
    int shots; //cantidad de disparos que tiene la torre, se disminuirá conforme los ejecute

    public:
    Tower(); //constructor por defecto
    Tower(int row, int col, int damage, int shots, int attackRange); //constructor de asignación
    ~Tower();

    //getters and setters
    int getRow();
    int getCol();
    int getDamage();
    bool getTowersActivate();
    int getShots();
    int getAttackRange();

    void setTowersActivate(bool towersActivate);
    void setShots(int shots);
    void setRow(int row);
    void setCol(int col);
    void setDamage(int damage);
    void setAttackRange(int attackRange);

    //funciones:
    //#1 restar la cantidad de disparos y desactivar la torre cuando ya no tenga disparos disponibles
    void newShots();
    //#2 creamos una funcion que nos indica si la torre puede disparar o no (dependiendo de la cantidad de disparos que tenga)
    bool canShot();

};


#endif //PARTE_B_TOWER_H