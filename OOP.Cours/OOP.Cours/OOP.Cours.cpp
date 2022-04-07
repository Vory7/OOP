#include <iostream>
#include <list>
#include <conio.h>
#include <vector>
#include "windows.h"

#include "Creature.hpp"
#include "Carrot.hpp"
#include "Rabbit.hpp"
#include "Wolf.hpp"
#include "Map.hpp"

int size = 10;
int cs = 0;
int cn = 10;
int rn = 10;
int wn = 5;

std::list<Carrot*> MoveC(std::list<Carrot*> carrots, Map map);
std::list<Rabbit*> MoveR(std::list<Rabbit*> rabbits, Map map);
std::list<Wolf*> MoveW(std::list<Wolf*> wolves, Map map);

int main()
{
    setlocale(LC_ALL, "Russian");

    srand(time(NULL));
    std::cout << "Для старта игры нажмите пробел" << std::endl;

    if (_getch() != ' ') { return 0; }

    system("cls");

    Map map;
    int x, y, s;
    char name;

    std::list<Carrot*> carrots;
    std::list<Rabbit*> rabbits;
    std::list<Wolf*> wolves;
    

    for (int i = 0; i < cn; ++i) {
        while (true) {
            x = rand() % size;
            y = rand() % size;
            name = map.GetName(x, y);
            if (name == '_') break;
        }
        map.NewName(x,y, 'C');
        carrots.push_back(new Carrot(x, y));
    }

    for (int i = 0; i < rn; ++i) {
        while (true) {
            x = rand() % size;
            y = rand() % size;
            name = map.GetName(x, y);
            if (name == '_') break;
        }
        map.NewName(x, y, 'R');
        rabbits.push_back(new Rabbit(x, y));
    }

    for (int i = 0; i < wn; ++i) {
        while (true) {
            x = rand() % size;
            y = rand() % size;
            name = map.GetName(x, y);
            if (name == '_') break;
        }
        map.NewName(x, y, 'W');
        wolves.push_back(new Wolf(x, y));
    }


    while (true) {

        map.Print();

        std::cout << "Всего моркови - " << cn << std::endl;
        std::cout << "Всего кроликов - " << rn << std::endl;
        std::cout << "Всего волков - " << wn << std::endl;

        std::cout << "Для совершения одного хода нажмите пробел, для выхода из игры введите любую другую" << std::endl;

        if (_getch() != ' ') return 0;

        system("cls");

        carrots = MoveC(carrots, map);
        rabbits = MoveR(rabbits, map);
        int xc, yc, xr, yr, xw, yw;
        if ((carrots.empty() != 1) && (rabbits.empty() != 1)) {
            for (std::list<Carrot*>::iterator it1 = carrots.begin(); it1 != carrots.end();) {
                s = 0;
                xc = (*it1)->getX();
                yc = (*it1)->getY();
                for (std::list<Rabbit*>::iterator it = rabbits.begin(); it != rabbits.end(); ++it) {
                    xr = (*it)->getX();
                    yr = (*it)->getY();
                    if ((xc == xr) && (yc == yr)) {
                        s = 1;
                        break;
                    }
                }
                if (s == 1) it1 = carrots.erase(it1);
                else ++it1;

            }
        }
        wolves = MoveW(wolves, map);
        if ((wolves.empty() != 1) && (rabbits.empty() != 1)) {
            for (std::list<Rabbit*>::iterator it1 = rabbits.begin(); it1 != rabbits.end();) {
                s = 0;
                xr = (*it1)->getX();
                yr = (*it1)->getY();
                for (std::list<Wolf*>::iterator it = wolves.begin(); it != wolves.end(); ++it) {
                    xw = (*it)->getX();
                    yw = (*it)->getY();
                    if ((xw == xr) && (yw == yr)) {
                        s = 1;
                        break;
                    }
                }
                if (s == 1) it1 = rabbits.erase(it1);
                else ++it1;

            }
        }

        
    }
    
    return 0;
}

std::list<Carrot*> MoveC(std::list<Carrot*> carrots, Map map) {

    srand(time(NULL));

    std::list<Carrot*>::iterator it;

    int size = 10, s, x, y;

    for (it = carrots.begin(); it != carrots.end();) {
        (*it)->update();
        if ((*it)->GetLife() == 0) {
            --cn;
            x = (*it)->getX();
            y = (*it)->getY();
            map.Erase(x, y);
            it = carrots.erase(it);
        }
        else ++it;
    }

    ++cs;

    if (cs == 2) {
        cs = 0;
        s = (rand() % 3) + 2;
        for (int i = 0; i < s; ++i) {
            ++cn;
            while (1) {
                x = rand() % size;
                y = rand() % size;
                if (map.GetName(x, y) == '_') break;
            }
            map.NewName(x, y, 'C');
            carrots.push_back(new Carrot(x, y));
        }
    }

    return carrots;

    
}

std::list<Rabbit*> MoveR(std::list<Rabbit*> rabbits, Map map) {

    std::list<Rabbit*>::iterator it;

    int s, xr, yr, xr1, yr1;

    for (it = rabbits.begin(); it != rabbits.end();) {
        xr1 = (*it)->getX();
        yr1 = (*it)->getY();
        s = (*it)->update();
        if (s != 0) {
            while (true) {
                (*it)->Movement();
                xr = (*it)->getX();
                yr = (*it)->getY();
                if ((map.GetName(xr, yr) == '_') || ((map.GetName(xr, yr) == 'C'))) break;
                (*it)->Movement(xr1, yr1);
            }
        }

        xr = (*it)->getX();
        yr = (*it)->getY();

        if ((*it)->getHungry() <= 0) {
            --rn;
            map.Erase(xr1, yr1);
            it = rabbits.erase(it);
        }
        else {
            
            if (s == 1) {
                map.Erase(xr1, yr1);
            }
            else if (s == 2) {
                rabbits.push_back(new Rabbit(xr1, yr1));
                ++rn;
            }

            if (map.GetName(xr, yr) == 'C') {
                --cn;
                (*it)->Eat();
            }

            map.NewName(xr, yr, 'R');

            ++it;
        }
    }

    return rabbits;


}

std::list<Wolf*> MoveW(std::list<Wolf*> wolves, Map map) {

    std::list<Wolf*>::iterator it;

    int s, xw, yw, xw1, yw1;

    for (it = wolves.begin(); it != wolves.end();) {
        xw1 = (*it)->getX();
        yw1 = (*it)->getY();
        s = (*it)->update();
        if (s != 0) {
            while (true) {
                (*it)->Movement();
                xw = (*it)->getX();
                yw = (*it)->getY();
                if ((map.GetName(xw, yw) == '_') || (map.GetName(xw, yw) == 'R')) break;
                (*it)->Movement(xw1, yw1);
            }
        }

        xw = (*it)->getX();
        yw = (*it)->getY();

        if ((*it)->getHungry() <= 0) {
            --wn;
            map.Erase(xw1, yw1);
            it = wolves.erase(it);
        }
        else {

            if (s == 1) {
                map.Erase(xw1, yw1);
            }
            else if (s == 2) {
                wolves.push_back(new Wolf(xw1, yw1));
                ++wn;
            }

            if (map.GetName(xw, yw) == 'R') {
                --rn;
                (*it)->Eat();
            }

            map.NewName(xw, yw, 'W');

            ++it;
        }
    }

    if (wn < 5) {
        s = 0;
        while (wn < 5) {
            xw = 0;
            yw = 0;
            while (true) {
                while (true) {
                    if (map.GetName(xw, yw) == '_')
                    {
                        s = 2;
                        break;
                    }
                    ++xw;
                    if (xw == (size - 1)) {
                        if (yw = size - 1) break;
                        xw = 0;
                        yw = size - 1;
                    }
                }
                xw = 0;
                yw = 0;
                while (true) {
                    if (map.GetName(xw, yw) == '_') 
                    {
                        s = 2;
                        break;
                    }
                    ++yw;
                    if (yw == (size - 1)) {
                        if (xw = size - 1) break;
                        yw = 0;
                        xw = size - 1;
                    }
                }
                if (s == 2) break;
                s = 1;

            }
            if (s == 1) break;
            map.NewName(xw, yw, 'W');
            wolves.push_back(new Wolf(xw, yw));
            ++wn;
        }
    }

    return wolves;


}