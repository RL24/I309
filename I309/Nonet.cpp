//
// Created by Feignex on 16/05/2017.
//

#include "Nonet.h"

/**
 * Standard constructor of nonet
 * @param x The nonets base column
 * @param y The nonets base row
 */
Nonet::Nonet(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
 * Get the nonets base column
 * @return The base column of the nonet
 */
int Nonet::getX() {
    return x;
}

/**
 * Get the nonets base row
 * @return The base row of the nonet
 */
int Nonet::getY() {
    return y;
}

/**
 * Get the list of cells in the nonet
 * @return The list of cells in the nonet
 */
list <Cell> Nonet::getCells() {
    return cells;
}

/**
 * Add a cell to the nonet
 * @param cell The cell to add
 */
void Nonet::addCell(Cell cell) {
    cells.push_front(cell);
}

/**
 * Remove a cell from the nonet
 * @param cell The cell to remove
 */
void Nonet::removeCell(Cell cell) {
    cells.remove(cell);
}

/**
 * Get the list of available numbers
 * @return The list of available numbers
 */
list<int> Nonet::getAvailable() {
    return available;
}

/**
 * Add a value to the available number selection
 * @param value The value to add
 */
void Nonet::addAvailable(int value) {
    this->available.push_front(value);
}

/**
 * Remove a value from the available number selection
 * @param value The value to remove
 */
void Nonet::removeAvailable(int value) {
    this->available.remove(value);
}
