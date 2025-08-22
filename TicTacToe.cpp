#include "TicTacToe.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

TicTacToe::TicTacToe() {
    // Initialize the board
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }

    // Initialize random seed
    srand(time(NULL));

    // Flip a coin to see who goes first
    if (rand() % 2 == 0) {
        machineSymbol = 'O';
        playerSymbol = 'X';
        machineMove();
        cout << "Machine win the coin flip so it will go first!!!"<< endl;
    } else {
        machineSymbol = 'X';
        playerSymbol = 'O';
        cout << "Player win the coin flip so you will go first!!!"<< endl;
    }
}

void TicTacToe::printBoard() {
    cout << board[0] << "|" << board[1] << "|" << board[2] << "\n";
    cout << "-+-+-\n";
    cout << board[3] << "|" << board[4] << "|" << board[5] << "\n";
    cout << "-+-+-\n";
    cout << board[6] << "|" << board[7] << "|" << board[8] << "\n";
}

void TicTacToe::playerMove() {
    // Ask the player for their move
    int position;
    do {
        cout << "Enter a position 1-9 (From left to right!!!): ";
        cin >> position;
        position--; // Convert to zero-based index

        if (position < 0 || position > 8) {
            cout << "Invalid position!\n";
        } else if (board[position] != ' ') {
            cout << "That position is already taken!\n";
        }
    } while (position < 0 || position > 8 || board[position] != ' ');

    // Update the board
    board[position] = playerSymbol;
}

void TicTacToe::machineMove() {
    // Determine the machine's move and update the board
    int machinePosition;
    if (machineRule1(machinePosition) ||
        machineRule2(machinePosition) ||
        machineRule3(machinePosition) ||
        machineRule4(machinePosition) ||
        machineRule5(machinePosition)) {
        board[machinePosition] = machineSymbol;
    }
}

bool TicTacToe::machineRule1(int &position) {
    // Check if the machine or player can win
    char symbol = (machineSymbol == 'X') ? 'O' : 'X';
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = symbol;
            if (checkWin(symbol)) {
                position = i;
                board[i] = ' ';
                return true;
            }
            board[i] = ' ';
        }
    }
    return false;
}

bool TicTacToe::machineRule2(int &position) {
    // Check if the center is open
    if (board[4] == ' ') {
        position = 4;
        return true;
    }
    return false;
}

bool TicTacToe::machineRule3(int &position) {
    // Check if the player has filled a corner
    char symbol = (machineSymbol == 'X') ? 'O' : 'X';
    if ((board[0] == symbol && board[8] == ' ') ||
        (board[2] == symbol && board[6] == ' ') ||
        (board[6] == symbol && board[2] == ' ') ||
        (board[8] == symbol && board[0] == ' ')) {
        position = (board[0] == symbol) ? 8 :
                   (board[2] == symbol) ? 6 :
                   (board[6] == symbol) ? 2 : 0;
        return true;
    }
    return false;
}

bool TicTacToe::machineRule4(int &position) {
    // Fill in any corner
    if (board[0] == ' ') {
        position = 0;
    } else if (board[2] == ' ') {
        position = 2;
    } else if (board[6] == ' ') {
        position = 6;
    } else if (board[8] == ' ') {
        position = 8;
    } else {
        return false; // No empty corner available
    }
    return true;
}

bool TicTacToe::machineRule5(int &position) {
    // Fill in the first available place
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            position = i;
            return true;
        }
    }
    return false; // No empty place available
}

bool TicTacToe::checkWin(char symbol) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == symbol && board[i + 1] == symbol && board[i + 2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == symbol && board[i + 3] == symbol && board[i + 6] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if (board[0] == symbol && board[4] == symbol && board[8] == symbol) {
        return true;
    }

    if (board[2] == symbol && board[4] == symbol && board[6] == symbol) {
        return true;
    }

    // No win
    return false;
}

bool TicTacToe::isTie() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

void TicTacToe::play() {
    while (true) {
        printBoard();

        // Check if player wins
        if (checkWin(playerSymbol)) {
            cout << "You win!\n";
            break;
        }

        // Check if it's a tie
        if (isTie()) {
            cout << "It's a tie!\n";
            break;
        }

        playerMove();

        // Check if player wins after their move
        if (checkWin(playerSymbol)) {
            printBoard();
            cout << "You win!\n";
            break;
        }

        // Check if it's a tie after player's move
        if (isTie()) {
            printBoard();
            cout << "It's a tie!\n";
            break;
        }

        machineMove();

        // Check if machine wins after its move
        if (checkWin(machineSymbol)) {
            printBoard();
            cout << "Machine wins!\n";
            break;
        }
    }
}

