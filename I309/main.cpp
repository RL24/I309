//Include necessary libraries
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

//Disable the need to use "std::<method>"
using namespace std;

//Declare methods (must be done prior to method calls)
bool isRowValid(string *row);
void replaceString(string *str, string from, string to);

const int COLUMNS = 9;
const int ROWS = 9;

//Main function
int main() {
    //Initial welcome message
    cout << "Welcome to a console sudoku solver. Please enter each of the 9 rows:" << endl;
    cout << "(tip: use ? or - for unknown/blank squares in the sudoku)" << endl;
    cout << "(spaces are optional, e.g.: ??? 4?7 ?9?)" << endl << endl;

    //Array to store the users input
    string rows[ROWS];

    //Get the users input
    for (int i = 0; i < ROWS; i++) {
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
    for (int i = 0; i < ROWS; i++) {
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

    int grid[ROWS][COLUMNS];

    //Convert the user input to a more usable format
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {
            //Negate by the int value of '0' to ensure the content of value is 0-9
            int value = rows[x][y] - '0';

            //If the value is not 0-9, set to -1 to represent an unknown grid cell
            if (value < 0 || value > 9)
                value = -1;

            grid[x][y] = value;
        }
    }

    //Attempt to solve the sudoku
    bool solved = false;
    while (!solved) {
        for (int x = 0; x < COLUMNS; x++) {
            for (int y = 0; y < ROWS; y++) {
                int currentCell = grid[x][y];

                //If the current cell is already known, skip it
                if (currentCell != -1)
                    continue;

                //Find the current box coordinates
                int boxX = (int) ceil(x / 3.) * 3;
                int boxY = (int) ceil(y / 3.) * 3;

                //Find the numbers that are already taken
                vector<int> box;
                vector<int> column;
                vector<int> row;

                //Current box
                for (int bx = 0; bx < 3; bx++) {
                    for (int by = 0; by < 3; by++) {
                        int next = grid[boxX + bx][boxY + by];
                        if (next != -1)
                            box.push_back(next);
                    }
                }

                //Column
                for (int c = 0; c < COLUMNS; c++) {
                    int next = grid[c][y];
                    if (next != -1)
                        column.push_back(next);
                }

                //Row
                for (int r = 0; r < ROWS; r++) {
                    int next = grid[x][r];
                    if (next != -1)
                        row.push_back(next);
                }

                
            }
        }
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
    return len == COLUMNS && row->find_first_not_of("0123456789?-") == string::npos;
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