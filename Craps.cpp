#include "Craps.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

Craps::Craps() noexcept {
    // Initialize random seed
    srand(time(NULL));

    // Set initial player money
    money = 50;
}

void Craps::play() {
    char playAgain = 'y';
    while (playAgain == 'y' && money > 0) {
        // Get player's bet
        int bet;
        do {
            cout << "You have $" << fixed << setprecision(2) << money << ". Place your bet: ";
            cin >> bet;
            if (bet > money) {
                cout << "You can't bet more than you have.\n";
            }
        } while (bet > money);

        // Roll the dice
        int roll1 = rollDice();
        int roll2 = rollDice();
        int total = roll1 + roll2;
        cout << "You rolled a " << roll1 << " and a " << roll2 << " for a total of " << total << ".\n";

        // Check for instant win/loss
        if (total == 7 || total == 11) {
            cout << "You win!\n";
            money += bet;
            cout << "Your net worth is now $" << fixed << setprecision(2) << money << ".\n";
        } else if (total == 2 || total == 3 || total == 12) {
            cout << "You lose!\n";
            money -= bet;
            cout << "Your net worth is now $" << fixed << setprecision(2) << money << ".\n";
        } else {
            // Establish the point
            int point = total;
            cout << "Establishing point: " << point << "\n";
            do {
                // Roll the dice again
                roll1 = rollDice();
                roll2 = rollDice();
                total = roll1 + roll2;
                cout << "You rolled: " << roll1 << " + " << roll2 << " = " << total << ".\n";

                // Check for win/loss
                if (total == point) {
                    cout << "You win!\n";
                    money += bet;
                    cout << "Your net worth is now $" << fixed << setprecision(2) << money << ".\n";
                } else if (total == 7) {
                    cout << "You lose!\n";
                    money -= bet;
                    cout << "Your net worth is now $" << fixed << setprecision(2) << money << ".\n";
                }
            } while (total != point && total != 7);
        }

        // Ask player if they want to play again
        if (money > 0) {
            cout << "Do you want to play again? (y/n) ";
            cin >> playAgain;
        } else {
            cout << "You're out of money!\n";
        }
    }

    // Display final player money
    cout << "You leave with $" << fixed << setprecision(2) << money << ".\n";
}

int Craps::rollDice() {
    return rand() % 6 + 1;
}
