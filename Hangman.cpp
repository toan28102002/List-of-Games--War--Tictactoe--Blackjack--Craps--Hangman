#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Hangman::Hangman() {
    // Load words from file
    ifstream file("words.txt");
    string word;
    while (file >> word) {
        words.push_back(word);
    }

    // Initialize random seed
    srand(time(NULL));
}

void Hangman::play() {
    // Choose a random word
    string word = words[rand() % words.size()];
    string guessWord(word.length(), '?');

    // Play the game
    int numGuesses = 6;
    bool gameOver = false;
    while (!gameOver) {
        // Display the guess word and remaining guesses
        cout << endl;
        cout << "Word: " << guessWord << "\n";
        cout << "Guesses remaining: " << numGuesses << "\n";

        // Get the player's guess
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;

        // Check if the guess is correct
        bool correctGuess = false;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                guessWord[i] = guess;
                correctGuess = true;
                cout << "Nice Guess! " << numGuesses << " guesses remaining.\n";
            }
        }

        // Decrement remaining guesses if incorrect guess
        if (!correctGuess) {
            numGuesses--;
            if (numGuesses == 0) {
                cout << "Invalid guess! The word was " << word << ".\n";
            } else {
                cout << "Invalid guess! " << numGuesses << " guesses remaining.\n";
            }
        }

        // Check if game is over
        if (numGuesses == 0) {
            gameOver = true;
        } else if (guessWord == word) {
            cout << "Nice guess! You win!\n";
            gameOver = true;
        }
    }
}
