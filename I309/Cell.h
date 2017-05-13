#include <iostream>
#include <list>

using namespace std;

class Cell {
private:
    int x, y, value;
    list<int> available;
public:
    Cell(int x, int y, int value);
    int getX();
    int getY();
    int getValue();
    list<int> getAvailable();
};