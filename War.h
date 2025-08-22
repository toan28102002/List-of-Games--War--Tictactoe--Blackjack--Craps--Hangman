#ifndef WAR_H
#define WAR_H

#include <vector>
#include <string>

class War {
public:
    War();
    void play();

private:
    std::vector<int> deck;
    std::vector<int> playerHand;
    std::vector<int> computerHand;
    std::vector<int> holdCards;
    int playerScore;
    int computerScore;

    void initializeDeck();
    void shuffleDeck();
    void dealCards();
    int drawCard(std::vector<int>& hand);
    std::string cardToString(int card);
    std::string compareCards(int playerCard, int computerCard);
    void playRound();
    void playWar();
    bool checkWinner();
};

#endif
