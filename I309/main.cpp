//Include necessary libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include "Cell.h"
#include "Nonet.h"

//Disable the need to use "std::<method>"
using namespace std;

//Declare methods (must be done prior to method calls)
bool isRowValid(string *row);
void replaceString(string *str, string from, string to);

const int NONET_SIZE = 3;
const int GRID_SIZE = NONET_SIZE * 3;

//Main function
int main() {
    //Initial welcome message
    cout << "Welcome to a console sudoku solver. Please enter each of the 9 rows:" << endl;
    cout << "(tip: use ? or - for unknown/blank squares in the sudoku)" << endl;
    cout << "(spaces are optional, e.g.: ??? 4?7 ?9?)" << endl << endl;

    //Array to store the users input
    string rows[GRID_SIZE];

    //Get the users input
    for (int i = 0; i < GRID_SIZE; i++) {
        getline(cin, rows[i]);

        //Ensure the user actually entered something (or that they entered a blank line to fulfill the layout of a sudoku)
        if (rows[i].length() == 0) {
            i--;
            continue;
        }

        //Format the input for simpler parsing and validation
        replaceString(&rows[i], " ", "");
    }

    //Validate each row and ensure the user inputs a new row for every invalid one
    for (int i = 0; i < GRID_SIZE; i++) {
        while (!isRowValid(&rows[i])) {
            system("cls");
            cout << "Row " << i + 1 << " is invalid:" << endl;
            cout << rows[i] << endl << endl;
            cout << "Please re-enter row " << i + 1 << ":" << endl;

            //Get the new formatted row input
            getline(cin, rows[i]);
            replaceString(&rows[i], " ", "");
        }
    }

    cout << "Validated" << endl;

    Nonet nonets[NONET_SIZE][NONET_SIZE];
    Cell grid[GRID_SIZE][GRID_SIZE];

    //Convert the user input to a more usable format
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            //Negate by the int value of '0' to ensure the content of value is 0-9
            int value = rows[x][y] - '0';

            //If the value is not 0-9, set to -1 to represent an unknown grid cell
            if (value < 0 || value > 9)
                value = -1;

            grid[x][y] = Cell(x, y, value);
        }
    }
    cout << "Created grid" << endl;

    /**
     * New solve method, iterate over each "nonet" (3x3 square), give each square all available numbers in
     * the current nonet, iterate over each cell in the nonet, if each number available is already
     * in the same row or column of the current cell, remove it from the available for that cell. If the
     * cells available numbers only has one remaining, that is the number for that cell. Thinking of the
     * algorithm I'll need to do this is yet for me to figure out, but I'm somewhat positive that it will
     * require refactoring multiple times
     */

    for (int bx = 0; bx < GRID_SIZE; bx+= NONET_SIZE) {
        for (int by = 0; by < GRID_SIZE; by+= NONET_SIZE) {
            Nonet nonet = Nonet(bx, by);
            nonets[bx / NONET_SIZE][by / NONET_SIZE] = nonet;
            for (int x = bx; x < bx + NONET_SIZE; x++) {
                for (int y = by; y < by + NONET_SIZE; y++) {
                    Cell cell = grid[x][y];
                    nonet.addCell(cell);
                    if (cell.getValue() != -1)
                        nonet.removeAvailable(cell.getValue());
                }
            }
            cout << bx << "," << by << ": " << nonet.getAvailable().size() << endl;
        }
    }

    cout << "Created nonets" << endl;

    for (int bx = 0; bx < NONET_SIZE; bx++) {
        for (int by = 0; by < NONET_SIZE; by++) {
            Nonet nonet = nonets[bx][by];
            cout << nonet.getAvailable().size() << endl;
            for (int x = 0; x < NONET_SIZE; x++) {
                for (int y = 0; y < NONET_SIZE; y++) {
                    int cx = nonet.getX() + x;
                    int cy = nonet.getY() + y;

                    Cell cell = grid[cx][cy];
                    if (cell.getValue() == -1) {
                        cell.addAvailable(nonet.getAvailable());

                        for (int z = 0; z < GRID_SIZE; z++) {
                            Cell nextColumn = grid[z][cy];
                            Cell nextRow = grid[cx][z];
                            //if (find(cell.getAvailable().begin(), cell.getAvailable().end(), nextColumn.getValue()) != cell.getAvailable().end())
                            cell.removeAvailable(nextColumn.getValue());
                            //if (find(cell.getAvailable().begin(), cell.getAvailable().end(), nextRow.getValue()) != cell.getAvailable().end())
                            cell.removeAvailable(nextRow.getValue());
                        }

                        if (cell.getAvailable().size() == 1)
                            cell.setValue(cell.getAvailable().back());
                    }
                }
            }
        }
    }

    //TODO: solve the sudoku, and clear the console window and print out the percentage of sudoku completion

    //Clear the console window
    //system("cls");

    //Print out the final sudoku solution
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            Cell cell = grid[x][y];
            cout << (cell.getValue() == -1 ? "-" : to_string(cell.getValue()));
            if ((y + 1) % 3 == 0)
                cout << " ";
        }
        cout << endl;
        if ((x + 1) % 3 == 0)
            cout << endl;
    }

    int a;
    cin >> a;

    return 0;
}

//Define a body for the declared methods above

/**
 * Check that the row length matches the required, and the input only contains valid characters "0-9, ?, -"
 * @param row The input string to check validation on
 * @return Whether or not the row is valid
 */
bool isRowValid(string *row) {
    int len = row->length();
    return len == GRID_SIZE && row->find_first_not_of("0123456789?-") == string::npos;
}

/**
 * Replace substrings in a string with another
 * @param str The string to replace substrings in
 * @param from The substring to replace
 * @param to The substring to insert
 */
void replaceString(string *str, string from, string to) {
    size_t pos = 0;
    //While the input string contains "from", replace text from "pos" to "pos + to.length" with "to"
    while ((pos = str->find(from, pos)) != string::npos) {
        str->replace(pos, from.length(), to);
        pos+= to.length();
    }
}