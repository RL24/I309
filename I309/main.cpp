//Include necessary libraries
#include <iostream>
#include <algorithm>
#include <vector>

//Disable the need to use "std::<method>"
using namespace std;

//Declare methods (must be done prior to method calls)
bool isRowValid(string *row);
void replaceString(string *str, string from, string to);

//Main function
int main() {
    //Initial welcome message
    cout << "Welcome to a console sudoku solver. Please enter each of the 9 rows:" << endl;
    cout << "(tip: use ? or - for unknown/blank squares in the sudoku)" << endl;
    cout << "(spaces are optional, e.g.: ??? 4?7 ?9?)" << endl << endl;

    //Array to store the users input
    const int rowCount = 3;
    string rows[rowCount];

    //Get the users input
    for (int i = 0; i < rowCount; i++) {
        getline(cin, rows[i]);

        //Ensure the user actually entered something (or that they entered a blank line to fulfill the layout of a sudoku)
        if (rows[i].length() == 0) {
            i--;
        }
    }

    //Format the input for simpler parsing and validation
    for (int i = 0; i < rowCount; i++) {
        replaceString(&rows[i], " ", "");
        cout << rows[i] << endl;
    }

    for (int i = 0; i < rowCount; i++) {
        while (!isRowValid(&rows[i])) {
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
    return len == 9 && row->find_first_not_of("0123456789?-") == string::npos;
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