// TicTacToe.h

#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe {
public:
    TicTacToe();
    void play();
    void printBoard();
    void playerMove();
    void machineMove();
    bool checkWin(char symbol);
    bool machineRule1(int &position);
    bool machineRule2(int &position);
    bool machineRule3(int &position);
    bool machineRule4(int &position);
    bool machineRule5(int &position);
    bool isTie(); // Add declaration of isTie() function
private:
    char board[9];
    char machineSymbol;
    char playerSymbol;
};

#endif // TICTACTOE_H
