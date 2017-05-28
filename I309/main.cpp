//Include necessary libraries
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <sstream>

//Disable the need to use "std::<method>"
using namespace std;

//Create some constant non-changing values
const int NONET_SIZE = 3;
const int GRID_SIZE = NONET_SIZE * 3;

//Declare methods (must be done prior to method calls)
bool isRowValid(string *row);

void replaceString(string *str, string from, string to);

bool inRow(int grid[GRID_SIZE][GRID_SIZE], int row, int value);

bool inRowPos(int grid[GRID_SIZE][GRID_SIZE][9], int row, int value);

bool inCol(int grid[GRID_SIZE][GRID_SIZE], int col, int value);

bool inColPos(int grid[GRID_SIZE][GRID_SIZE][9], int col, int value);

bool inBox(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int value);

bool inBoxPos(int grid[GRID_SIZE][GRID_SIZE][9], int row, int col, int value);

float floor(float value, float incremental);

int floor(int value, int incremental);

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

    int grid[GRID_SIZE][GRID_SIZE];
    int predefined[GRID_SIZE][GRID_SIZE];

    //Convert the user input to a more usable format
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            //Negate by the int value of '0' to ensure the content of value is 0-9
            int value = rows[x][y] - '0';

            //If the value is not 0-9, set to -1 to represent an unknown grid cell
            if (value < 0 || value > 9)
                value = -1;

            predefined[x][y] = value;
            grid[x][y] = value;
        }
    }
    cout << "Created grid" << endl;

    int possibilities[GRID_SIZE][GRID_SIZE][9];
    for (int x = 0; x < GRID_SIZE; x++)
        for (int y = 0; y < GRID_SIZE; y++)
            for (int z = 0; z < 9; z++)
                possibilities[x][y][z] = -1;

    bool solved = false;
    while (!solved) {
        solved = true;
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                if (grid[x][y] != -1)
                    continue;

                auto boxX = (int) (ceil(x / 3) * 3);
                auto boxY = (int) (ceil(y / 3) * 3);

                for (int z = 1; z <= 9; z++) {
                    if (!inRow(grid, x, z) && !inCol(grid, y, z)/* && !inBox(grid, boxX, boxY, z)*/) {
                        bool set = false;
                        for (int w = 0; w < 9; w++) {
                            if (possibilities[x][y][w] == -1) {
                                possibilities[x][y][w] = z;
                                set = true;
                                break;
                            }
                        }
                        if (set)
                            break;
                    }
                }
            }
        }

        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                if (grid[x][y] != -1)
                    continue;

                solved = false;

                auto boxX = (int) (ceil(x / 3) * 3);
                auto boxY = (int) (ceil(y / 3) * 3);

                //Iterate over the possibles and set them to -1 if its in another cell in the row col or boxes possibilities
                for (int z = 1; z <= 9; z++) {
                    if (!inRowPos(possibilities, x, z) && !inColPos(possibilities, y, z)/* && !inBoxPos(possibilities, boxX, boxY, z)*/) {
                        grid[x][y] = z;
                        break;
                    }
                }
            }
        }
    }
    //solveSudoku(grid, 0, 0);

    //TODO: solve the sudoku, and clear the console window and print out the percentage of sudoku completion

    //Clear the console window
    //system("cls");

    //Print out the final sudoku solution
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            int value = grid[x][y];
            cout << (value == -1 ? "-" : to_string(value));
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

//Define bodies for the declared methods above

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
        pos += to.length();
    }
}

/**
 * Check if the given value is in the specified row in the sudoku
 * @param grid The sudoku grid of known values
 * @param row The row to check in
 * @param value The value to check
 * @return If the row contains the value
 */
bool inRow(int grid[GRID_SIZE][GRID_SIZE], int row, int value) {
    for (int x = 0; x < GRID_SIZE; x++)
        if (grid[row][x] == value)
            return true;
    return false;
}

/**
 * Check if the given value is in the specified rows possibilities in the sudoku
 * @param grid The sudoku grid of known values
 * @param row The row to check in
 * @param value The value to check
 * @return If the rows possibilities contains the value
 */
bool inRowPos(int grid[GRID_SIZE][GRID_SIZE][9], int row, int value) {
    for (int x = 0; x < GRID_SIZE; x++)
        for (int z = 0; z < 9; z++)
            if (value != -1 && grid[row][x][z] == value)
                return true;
    return false;
}

/**
 * Check if the given value is in the specified column in the sudoku
 * @param grid The sudoku grid of known values
 * @param col The column to check in
 * @param value The value to check
 * @return If the column contains the value
 */
bool inCol(int grid[GRID_SIZE][GRID_SIZE], int col, int value) {
    for (int y = 0; y < GRID_SIZE; y++)
        if (grid[y][col] == value)
            return true;
    return false;
}

/**
 * Check if the given value is in the specified columns possibilities in the sudoku
 * @param grid The sudoku grid of known values
 * @param col The column to check in
 * @param value The value to check
 * @return If the columns possibilities contains the value
 */
bool inColPos(int grid[GRID_SIZE][GRID_SIZE][9], int col, int value) {
    for (int y = 0; y < GRID_SIZE; y++)
        for (int z = 0; z < 9; z++)
            if (value != -1 && grid[y][col][z] == value)
                return true;
    return false;
}

/**
 * Check if the given value is in the specified box in the sudoku
 * @param grid The sudoku grid of known values
 * @param row The base row of the box
 * @param col The base column of the box
 * @param value The value to check
 * @return If the box contains the value
 */
bool inBox(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int value) {
    for (int x = row; x < row + NONET_SIZE; x++)
        for (int y = col; y < col + NONET_SIZE; y++)
            if (grid[x][y] == value)
                return true;
    return false;
}

/**
 * Check if the given value is in the specified boxes possibilities in the sudoku
 * @param grid The sudoku grid possibilities of known values
 * @param row The base row of the box
 * @param col The base column of the box
 * @param value The value to check
 * @return If the boxes possibilities contains the value
 */
bool inBoxPos(int grid[GRID_SIZE][GRID_SIZE][9], int row, int col, int value) {
    for (int x = row; x < row + NONET_SIZE; x++)
        for (int y = col; y < col + NONET_SIZE; y++)
            for (int z = 0; z < 9; z++)
                if (value != -1 && grid[x][y][z] == value)
                    return true;
    return false;
}

/**
 * Floor a value to a given incremental multiplier (e.g. floor 75 to the nearest 20 mutliplier = 80 (20 * 4 = 80, 20 * 3 = 60, 75 is closer to 80))
 * @param value The value to floor
 * @param incremental The incremental value to floor to a multiplier of
 * @return The floored value to the nearest incremental multiplier
 */
float floor(float value, float incremental) {
    float one = 1 / incremental;
    return floor(value * one) / one;
}

/**Integer overload for float floor()**/
int floor(int value, int incremental) {
    return (int) floor((float) value, (float) incremental);
}