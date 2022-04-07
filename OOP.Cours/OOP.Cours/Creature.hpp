#ifndef CREATURE_H
#define CREATURE_H


#include <iostream>
#include <time.h>
#include "Map.hpp"

class Creature
{
protected:
    int x, y;
    char name;
    float hungry;

public:

    Creature(); 

    Creature(int x1, int y1) : x(x1), y(y1){};

    int getX() {
        return(x);
    }

    int getY() {
        return(y);
    }

    virtual void Eat() {
        hungry += 0.2;
    }

    virtual void Movement(int x1, int y1) {
        x = x1;
        y = y1;
    }
};
#endif