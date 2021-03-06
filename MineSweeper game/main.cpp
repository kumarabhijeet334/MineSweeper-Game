
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE 10

// Create a random grid creating function
// This function takes the difficulty, and array as argument
// It modifies a grid in return and returns it

void createGrid (int difLev, int playGrid[SIZE][SIZE]) {

    // Decide number of mines based on difficulty
    // For now, easy - 10 to 14 mines, medium - 15 to 18 mines, hard - 23 to 26 mines
    // To decide, can create an array or loop limit it
    int numMine = 0;
    switch (difLev) {
        case 1: numMine = 10 + rand()%5;
                break;
        case 2: numMine = 15 + rand()%5;
                break;
        case 3: numMine = 22 + rand()%5;
                break;
        default: cout << "Error: Difficulty level incorrectly specified, assuming medium...\n";
                 numMine = 15 + rand()%5;
                 break;
    }
    
    // Set the mines on the grid
    int posCol, posRow;
    posCol = posRow = 0;
    for (int i = 0; i < numMine; i++) {
        posRow = rand()%SIZE;
        posCol = rand()%SIZE;
        playGrid[posRow][posCol] = -1;
    }

    // Setting the Values
    // Use program mine162 for this
    int flag = 0;
    for (int i = 0; i < SIZE; i++) {
	    for (int j = 0; j < SIZE; j++) {

            // If the current cell is not a mine, then see the adjacent cells
            // And accordingly set its value
	        if(playGrid[i][j] != -1) {
		        if (playGrid[i-1][j] == -1 && (i-1)>=0) ++flag;
		        if (playGrid[i+1][j] == -1 && (i+1)<SIZE) ++flag;
		        if (playGrid[i][j-1] == -1 && (j-1)>=0) ++flag;
		        if (playGrid[i][j+1] == -1 && (j+1)<SIZE) ++flag;
		        if (playGrid[i+1][j+1] == -1 && (j+1)<SIZE && (i+1)<SIZE) ++flag;
		        if (playGrid[i-1][j-1] == -1 && (j-1)>=0 && (i-1)>=0) ++flag;
		        if (playGrid[i+1][j-1] == -1 && (j-1)>=0 && (i+1)<SIZE) ++flag;
		        if (playGrid[i-1][j+1] == -1 && (j+1)<SIZE && (i-1)>=0) ++flag;
                playGrid[i][j] = flag;
            }
	        flag = 0;
	    }
    }
}

// Create a reveal function

void reveal (char showGrid[SIZE][SIZE], int playGrid[SIZE][SIZE], int row, int col, bool select) {

    // If already discovered by another cell, then do not discover it again.
    // This is for speed and performance improvement
    // Implemented using the show grid instead of additional attribute
    if (showGrid[row][col] != '.' && showGrid[row][col] != 'P'){
        return;
    }

    // If Outside the bounds of the array, return
    if (row >= SIZE || row < 0 || col >= SIZE || col < 0){
        return;
    }

    // If it wasn't the selected cell of the player, proceed as follows
    if (select == false) {

        // If discovered cell is number, then return
        if (playGrid[row][col] > 0) {
                showGrid[row][col] = (char)(48 + playGrid[row][col]);
            return;
        }

        // If the discovered cell is empty, find other adjacent to it
        else if (playGrid[row][col] == 0) {
            showGrid[row][col] = '_';
            reveal(showGrid, playGrid, row, col - 1, 0);
            reveal(showGrid, playGrid, row, col + 1, 0);
            reveal(showGrid, playGrid, row - 1, col, 0);
            reveal(showGrid, playGrid, row + 1, col, 0);
            reveal(showGrid, playGrid, row + 1, col + 1, 0);
            reveal(showGrid, playGrid, row + 1, col - 1, 0);
            reveal(showGrid, playGrid, row - 1, col + 1, 0);
            reveal(showGrid, playGrid, row - 1, col - 1, 0);
        }
    }

    // If it was the selected cell, proceed as follows
    else {

        // Display the cell
        if (playGrid[row][col] == 0) showGrid[row][col] = '_';
        else if (playGrid[row][col] > 0) showGrid[row][col] = 48 + playGrid[row][col];

        // If the selected cell was empty, i.e zero cell, proceed as follows
        if (playGrid[row][col] == 0) {
            reveal(showGrid, playGrid, row, col - 1, 0);
            reveal(showGrid, playGrid, row, col + 1, 0);
            reveal(showGrid, playGrid, row - 1, col, 0);
            reveal(showGrid, playGrid, row + 1, col, 0);
            reveal(showGrid, playGrid, row + 1, col + 1, 0);
            reveal(showGrid, playGrid, row + 1, col - 1, 0);
            reveal(showGrid, playGrid, row - 1, col + 1, 0);
            reveal(showGrid, playGrid, row - 1, col - 1, 0);

        }
    }

    // In all other cases, including errors and selected cell a number cell, return
    return;
}

void display (char showGrid[SIZE][SIZE]) {
    cout << "    \033[1m0   1   2   3   4   5   6   7   8   9 \033[0m\n";
    cout << "  ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????\n";
    for (int i = 0; i < SIZE; i++){
        cout << "\033[1m" << i << "\033[0m ???";
        for (int j = 0; j < SIZE; j++){
            cout << " ";
            if (showGrid[i][j] == 'P') cout << "\033[31m???\033[0m ";
            else if (showGrid[i][j] == '.') cout << "  ";
            else if (showGrid[i][j] == '_') cout << "__";
            else if (showGrid[i][j] == '*') cout << "\033[1m???\033[0m ";
            else {
                if (showGrid[i][j] == '1') cout << "\033[32m";
                if (showGrid[i][j] == '2') cout << "\033[33m";
                if (showGrid[i][j] == '3') cout << "\033[36m";
                cout << showGrid[i][j] << "\033[0m ";
            }
            cout << "???";
        }
        cout << endl;
        if (i < (SIZE - 1)) {
            cout << "  ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????";
            cout << endl;
        }
    }
    cout << "  ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????" << endl;
}

int main () {
    srand(time(0));

    char showGrid[SIZE][SIZE];
    int playGrid[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            showGrid[i][j] = '.';
            playGrid[i][j] = 0;
        }
    }

    system("clear");

    cout << "???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????" << endl;
    cout << "???      "; cout << "\033[1mWelcome To Minesweeper v1.0\033[0m"; cout << "      ???" << endl;
    cout << "???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????" << endl;
    cout << "???"; cout << "       Select a difficulty level       "; cout << "???" << endl;
    cout << "???" << "Select 1 for Easy                      " << "???" << endl;
    cout << "???" << "Select 2 for Medium                    " << "???" << endl;
    cout << "???" << "Select 3 for Hard                      " << "???" << endl;
    cout << "???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????" << endl;
    cout << "\nYour choice: ";
    int diffLev = 0;
    cin >> diffLev;

    createGrid(diffLev, playGrid);

    system("clear");

    // Saving space for time measurements
    
    int check = 1;
    int ch = 2;
    int row = 0;
    int col = 0;
    
    while (ch != 3) {
        system("clear");
        display(showGrid);
        // Check for complete filling
        check = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                if (showGrid[i][j] == '.' && playGrid[i][j] != -1) {
                    check = 0;
                    break;
                }
            }
        }
        if (check) {
            for (int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                    if (playGrid[i][j] != -1 && (showGrid[i][j] == 'P' || showGrid[i][j] == '.')) {
                        check = 0;
                    }
                }
            }
            if (check) {
                cout << "YOU WIN !!";
                return 0;
            }
        }

        cout << "Enter 1 to place flag \033[31m" << "???" << "\033[0m\nEnter 2 to reveal cell\nEnter 3 to exit\nEnter Value: ";
        cin >> ch;
        if (ch == 3) {
            cout << "\nLeaving early? Okay!";
            return 1;
        }
        else {
            cout << "Enter indices for location (row then column): ";
            cin >> row >> col;
        }
        if (showGrid[row][col] != '.') {
            if (showGrid[row][col] != 'P') {
                cout << "Warning: Please enter an unfilled cell\n";
                continue;
            }
        }
        switch (ch){
            case 1: showGrid[row][col] = 'P';
                    break;
            case 2: if (playGrid[row][col] == -1){
                        // The Game Over sequence
                        for (int i = 0; i < SIZE; i++) {
                            for(int j = 0; j < SIZE; j++) {
                                if (playGrid[i][j] == -1) {
                                    showGrid[i][j] = '*';
                                }
                            }
                        }
                        system("clear");
                        display(showGrid);
                        cout << "You lose !!";
                        return 0;
                    }
                    reveal(showGrid, playGrid, row, col, true);
                    break;
            default: break;
        }

    }
    return 0;
}
