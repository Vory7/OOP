#ifndef CARROT_H
#define CARROT_H


#include <iostream>
#include <time.h>

#include "Creature.hpp"

class Carrot : public Creature
{

protected:

    int life;

public:

    Carrot(int x1, int y1) {
        x = x1;
        y = y1;
        name = 'C';
        life = 5;
    }

    void update() {
        --life;
    }

    int GetLife() {
        return(life);
    }

};



#endif