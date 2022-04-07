#ifndef RABBIT_H
#define RABBIT_H


#include <iostream>
#include <time.h>

#include "Creature.hpp"

class Rabbit : public Creature
{

protected:

    int dx, dy, speed, s;

public:

    Rabbit(int x1, int y1) {
        x = x1;
        y = y1;
        dx = 0;
        dy = 0;
        s = 2;
        name = 'R';
        hungry = 1;
        speed = 1;
    }

    int getDX() {
        return(dx);
    }

    int getDY() {
        return(dy);
    }

    float getHungry() {
        return(hungry);
    }

    int update() {
        --s;
        if (s == 0) {
            s = 2;
            hungry -= 0.2;
            int randome = rand() % 4;
            if (randome == 0) {
                hungry -= 0.2;
                return(2);
            }
            else return(1);
        }
        else return(0);
    }

    void Movement() {

        do {
            dx = (rand() % (2 + speed)) - speed;
            dy = (rand() % (2 + speed)) - speed;
        } while ((dx == 0) && (dy == 0));

        x += dx;
        y += dy;

        if ((x >= 9) || (x < 0))
        {
            dx *= -1;
            x += 2 * dx;
        }

        if ((y >= 9) || (y < 0))
        {
            dy *= -1;
            y += 2 * dy;
        }

    }

    void Movement(int x1, int y1) {
        x = x1;
        y = y1;
    }

    

};


#endif