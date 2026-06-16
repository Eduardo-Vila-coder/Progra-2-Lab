#ifndef PARTE_B_TOWER_H
#define PARTE_B_TOWER_H

//Permita multiples disparos
//Tenga rango de ataque
//Tenga dano configurable (1 - 5)


class Tower {
private:
    int row; //coordenadas de la torre
    int col;
    int damage; //daño que causa
    bool towerActivate; //para verificar si la torre está activa
    int shots; //cantidad de disparos que tiene la torre, se disminuirá conforme los ejecute
    int attackRange[12][2]= {{ 0,-2},{ 0, 2},{-2, 0},{ 2, 0},{-1,-2},{ 1,-2},{-1, 2},{ 1, 2},{-2,-1},{ 2,-1},{-2, 1},{ 2, 1}};

    public:
    Tower(); //constructor por defecto
    Tower(int row, int col, int damage, int shots); //constructor de asignación
    ~Tower();

    //getters and setters
    int getRow();
    int getCol();
    int getDamage();
    bool getTowersActivate();
    int getShots();

    void setTowersActivate(bool towersActivate);
    void setShots(int shots);
    void setRow(int row);
    void setCol(int col);
    void setDamage(int damage);

    //funciones:
    //#1 restar la cantidad de disparos y desactivar la torre cuando ya no tenga disparos disponibles
    void newShots();
};


#endif //PARTE_B_TOWER_H