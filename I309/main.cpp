//Include necessary libraries
#include <iostream>

//Disable the need to use "std::<method>"
using namespace std;

//Main function
int main() {
    //Initial welcome message
    cout << "Welcome to a console sudoku solver. Please enter each of the 9 rows:" << endl;
    cout << "(tip: use ? or - for unknown/blank squares in the sudoku)" << endl;
    cout << "(spaces are optional, e.g.: ??? 4?7 ?9?)" << endl << endl;

    //Array to store the users input
    string rows[9];

    //Get the users input
    for (int i = 0; i < 9; i++) {
        getline(cin, rows[i]);
    }

    return 0;
}