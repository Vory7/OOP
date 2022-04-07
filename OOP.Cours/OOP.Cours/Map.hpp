#ifndef MAP_H
#define MAP_H


#include <iostream>
#include <time.h>

class Map
{
protected:

    char** map;
    int size = 10;

public:

    Map() {
        map = new char * [size];
        for (int i = 0; i < size; ++i) {
            map[i] = new char[size];
            for (int j = 0; j < size; ++j) {
                map[i][j] = '_';
            }
        }
    }

    void Print() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) std::cout << map[i][j] << " ";
            std::cout << std::endl;
        }
    }

    char GetName(int x1, int y1) {
        return(map[x1][y1]);
    }

    void NewName(int x1, int y1, char name1) {
        map[x1][y1] = name1;
    }

    void Erase(int x1, int y1) {
        map[x1][y1] = '_';
    }

};

#endif