#include <iostream>
#include <list>

#ifndef I309_CELL
#define I309_CELL

using namespace std;

class Cell {
private:
    int x, y, value;
    list<int> available = {1, 2, 3, 4, 5, 6, 7, 8, 9};
public:
    Cell() {}
    Cell(int x, int y, int value);

    int getX();
    int getY();
    int getValue();
    void setValue(int value);

    list<int> getAvailable();
    void addAvailable(int value);
    void addAvailable(list<int> values);
    void removeAvailable(int value);

    bool operator==(Cell cell);
};

#endif