#include <iostream>
#include <list>
#include "Cell.h"

#ifndef I309_NONET
#define I309_NONET

using namespace std;

class Nonet {
private:
    int x, y;
    list<Cell> cells;
    list<int> available = {1, 2, 3, 4, 5, 6, 7, 8, 9};
public:
    Nonet() {}
    Nonet(int x, int y);
    int getX();
    int getY();
    list<Cell> getCells();
    void addCell(Cell cell);
    void removeCell(Cell cell);
    list<int> getAvailable();
    void addAvailable(int value);
    void removeAvailable(int value);
};

#endif