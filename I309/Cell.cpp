#include "Cell.h"

/**
 * Standard constructor of cell
 * @param x The cells column
 * @param y The cells row
 * @param value The number in the current cell
 */
Cell::Cell(int x, int y, int value) {
    this->x = x;
    this->y = y;
    this->value = value;
}

/**
 * Get the cells column
 * @return The column the cell is in
 */
int Cell::getX() {
    return x;
}

/**
 * Get the cells row
 * @return The row the cell is in
 */
int Cell::getY() {
    return y;
}

/**
 * Get the number in the current cell
 * @return The cells value
 */
int Cell::getValue() {
    return value;
}

/**
 * Get the list of available numbers
 * @return The list of available numbers
 */
list<int> Cell::getAvailable() {
    return available;
}