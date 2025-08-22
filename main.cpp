//Name: Toan Nguyen (TOM)
//Class: 004 -  MWF 12:00-12:50
//Programming Assignment # 4 List of games
//Source use: 
// Black Jack: https://www.youtube.com/watch?v=MvX4tVETjHk and https://www.youtube.com/watch?v=Npj6JUnaKIE
//Craps: https://www.youtube.com/watch?v=hAtYYNelR3I
//TikTacToe: https://www.youtube.com/watch?v=dv_75WfQ1rA
// War game: https://github.com/Class-Warfare/War-Card-Game 



#include <iostream>
#include "Blackjack.h"
#include "Craps.h"
#include "Hangman.h"
#include "TicTacToe.h"
#include "War.h"
using namespace std;

int main() {
    // Display the list of games
    cout << "Games List \n";
    cout << "B - Blackjack\n";
    cout << "C - Craps\n";
    cout << "H - Hangman\n";
    cout << "T - TicTacToe\n";
    cout << "W - War\n";
    cout << "Q - Quit\n";
    
    // Ask the user to choose a game
    char choice;
    cout << "Please enter the letter of the game you want to play: ";
    cin >> choice;
    cout << endl;

    // Play the game based on the user's choice
    switch (toupper(choice)) {
        case 'B':
            // Play Blackjack
            {
                Blackjack bj;
                bj.play();
            }
            break;
        case 'C':
            // Play Craps
            {
                Craps craps;
                craps.play();
            }
            break;
        case 'H':
          {
                Hangman game;
                game.play();
          }
            break;
        case 'T':
          {
            TicTacToe game;
            game.play();
          }
            break;
        case 'W':
          {
             War game;
            game.play();
            break;
          }
        case 'Q':
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice!\n";
            break;
    }
    
    return 0;
}
