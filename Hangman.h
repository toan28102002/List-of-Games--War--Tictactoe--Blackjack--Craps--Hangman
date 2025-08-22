#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>
#include <string>

class Hangman {
public:
    Hangman();

    void play();

private:
    std::vector<std::string> words;
    std::string chosenWord;
    std::string guessWord;
    int guessesLeft;

    void loadWords();
    void chooseWord();
    void playRound();
    bool isGameOver();
    void printHangman();
    void printGuessWord();
};

#endif /* HANGMAN_H */
