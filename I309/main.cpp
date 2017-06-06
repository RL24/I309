//Include necessary libraries
#include <iostream>

//Disable the need to use "std::<method>"
using namespace std;

//Create some constant non-changing values (grid size, and empty value)
const int GS = 9;
const int UV = -1;

//Declare methods (must be done prior to method calls)
bool isRowValid(string *row);

void replaceString(string *str, string from, string to);

bool isEmpty(int grid[GS][GS], int &row, int &col);

bool inRow(int grid[GS][GS], int row, int value);

bool inCol(int grid[GS][GS], int col, int value);

bool inBox(int grid[GS][GS], int row, int col, int value);

bool solve(int grid[GS][GS]);

//Main function
int main() {
    //Initial welcome message
    cout << "Welcome to a console sudoku solver. Please enter each of the 9 rows:" << endl;
    cout << "(tip: use ? or - for unknown/blank squares in the sudoku)" << endl;
    cout << "(spaces are optional, e.g.: ??? 4?7 ?9?)" << endl << endl;

    //Array to store the users input
    string rows[GS];

    //Get the users input
    for (int i = 0; i < GS; i++) {
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
    for (int i = 0; i < GS; i++) {
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

    int grid[GS][GS];

    //Convert the user input to a more usable format
    for (int x = 0; x < GS; x++) {
        for (int y = 0; y < GS; y++) {
            //Negate by the int value of '0' to ensure the content of value is 0-9
            int value = rows[x][y] - '0';

            //If the value is not 0-9, set to "UV" to represent an unknown grid cell
            if (value < 0 || value > 9)
                value = UV;

            grid[x][y] = value;
        }
    }

    cout << "Created grid" << endl;

    solve(grid);

    //TODO: solve the sudoku, and clear the console window and print out the percentage of sudoku completion

    //Clear the console window
    //system("cls");

    //Print out the final sudoku solution
    for (int x = 0; x < GS; x++) {
        for (int y = 0; y < GS; y++) {
            int value = grid[x][y];
            cout << (value == UV ? "-" : to_string(value));
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
    return len == GS && row->find_first_not_of("0123456789?-") == string::npos;
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

bool isEmpty(int grid[GS][GS], int &row, int &col) {
    for (row = 0; row < GS; row++)
        for (col = 0; col < GS; col++)
            if (grid[row][col] == UV)
                return true;
    return false;
}

/**
 * Check if the given value is in the specified row in the sudoku
 * @param grid The sudoku grid of known values
 * @param row The row to check in
 * @param value The value to check
 * @return If the row contains the value
 */
bool inRow(int grid[GS][GS], int row, int value) {
    for (int x = 0; x < GS; x++)
        if (grid[row][x] == value)
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
bool inCol(int grid[GS][GS], int col, int value) {
    for (int y = 0; y < GS; y++)
        if (grid[y][col] == value)
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
bool inBox(int grid[GS][GS], int row, int col, int value) {
    for (int x = row; x < row + NONET_SIZE; x++)
        for (int y = col; y < col + NONET_SIZE; y++)
            if (grid[x][y] == value)
                return true;
    return false;
}

/**
 * Attempt to solve the sudoku using recursion
 * @param grid The sudoku grid of known values
 * @param row The row to check
 * @param col The column to check
 * @return If the cell has been solved
 */
bool solve(int grid[GS][GS]) {
    int row, col;
    //Get the next empty cell, set "row" and "cell" values of the pointer to the empty cell
    if (!isEmpty(grid, row, col))
        return true;
    for (int i = 1; i <= 9; i++) {
        //Check if the value "i" is not found in any other cell in the same row, column, and box
        if (!inRow(grid, row, i) && !inCol(grid, col, i) && !inBox(grid, row - row % 3, col - col % 3, i)) {
            grid[row][col] = i;
            //Use recursion to solve other cells, if they all return true in the end, then the sudoku has been solved
            if (solve(grid))
                return true;
            //Otherwise set the cell to the designated "empty" value
            grid[row][col] = UV;
        }
    }
    return false;
}