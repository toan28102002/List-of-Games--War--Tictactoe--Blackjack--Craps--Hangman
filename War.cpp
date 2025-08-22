#include "War.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

War::War() {
    initializeDeck();
    shuffleDeck();
    dealCards();
    playerScore = 0;
    computerScore = 0;
}

void War::initializeDeck() {
    for (int i = 0; i < 52; i++) {
        deck.push_back(i);
    }
}

void War::shuffleDeck() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        std::swap(deck[i], deck[j]);
    }
}

void War::dealCards() {
    for (int i = 0; i < 52; i += 2) {
        playerHand.push_back(deck[i]);
        computerHand.push_back(deck[i+1]);
    }
}

int War::drawCard(vector<int>& hand) {
    int card = hand.front();
    hand.erase(hand.begin());
    return card;
}

string War::cardToString(int card) {
    string valueString;
    string suitString;

    int value = card % 13;
    if (value == 0) {
        valueString = "Ace";
    }
    else if (value == 10) {
        valueString = "Jack";
    }
    else if (value == 11) {
        valueString = "Queen";
    }
    else if (value == 12) {
        valueString = "King";
    }
    else {
        valueString = to_string(value + 1);
    }

    int suit = card / 13;
    if (suit == 0) {
        suitString = "Hearts";
    }
    else if (suit == 1) {
        suitString = "Diamonds";
    }
    else if (suit == 2) {
        suitString = "Clubs";
    }
    else if (suit == 3) {
        suitString = "Spades";
    }

    return valueString + " of " + suitString;
}

string War::compareCards(int playerCard, int computerCard) {
    string playerString = cardToString(playerCard);
    string computerString = cardToString(computerCard);
    if (playerCard > computerCard) {
        return "Player wins round with " + playerString + ".";
    }
    else if (computerCard > playerCard) {
        return "Computer wins round with " + computerString + ".";
    }
    else {
        return "War! (" + playerString + " vs " + computerString + ")";
    }
}

void War::playRound() {
    cout << "Player Hand: ";
    for (int i = 0; i < playerHand.size(); i++) {
        cout << playerHand[i] << " ";
    }
    cout << endl;

    cout << "Computer Hand: ";
    for (int i = 0; i < computerHand.size(); i++) {
        cout << computerHand[i] << " ";
    }
    cout << endl;

    int playerCard = drawCard(playerHand);
    int computerCard = drawCard(computerHand);
    holdCards.push_back(playerCard);
    holdCards.push_back(computerCard);
    cout << "Player: " << playerCard << " vs Computer: " << computerCard << endl;
    string result = compareCards(playerCard, computerCard);
    cout << result << endl;
    if (result.find("Player") != string::npos) {
        playerScore += holdCards.size();
        playerHand.insert(playerHand.end(), holdCards.begin(), holdCards.end());
        holdCards.clear();
    }
    else if (result.find("Computer") != string::npos) {
        computerScore += holdCards.size();
        computerHand.insert(computerHand.end(), holdCards.begin(), holdCards.end());
        holdCards.clear();
    }
    else {
        playWar();
    }
}
void War::playWar() {
    if (playerHand.size() < 4) {
        cout << "Player does not have enough cards for war. Computer wins!" << endl;
        computerScore += playerHand.size() + computerHand.size() + holdCards.size();
        playerHand.clear();
        holdCards.clear();
        return;
    }
    else if (computerHand.size() < 4) {
        cout << "Computer does not have enough cards for war. Player wins!" << endl;
        playerScore += playerHand.size() + computerHand.size() + holdCards.size();
        computerHand.clear();
        holdCards.clear();
        return;
    }
    else {
        cout << "War!" << endl;
        for (int i = 0; i < 3; i++) {
            holdCards.push_back(drawCard(playerHand));
            holdCards.push_back(drawCard(computerHand));
        }
        playRound();
    }
}
bool War::checkWinner() {
    if (playerHand.size() < 10) {
        cout << "Computer wins! Player has less than 10 cards." << endl;
        return true;
    }
    else if (computerHand.size() < 10) {
        cout << "Player wins! Computer has less than 10 cards." << endl;
        return true;
    }
    else if (playerHand.size() + computerHand.size() <= 10) {
        if (playerHand.size() > computerHand.size()) {
            cout << "Player wins! Computer has less than 10 cards." << endl;
        }
        else if (computerHand.size() > playerHand.size()) {
            cout << "Computer wins! Player has less than 10 cards." << endl;
        }
        else {
            cout << "It's a tie! Both players have less than 10 cards." << endl;
        }
        return true;
    }
    return false;
}
void War::play() {
    bool winner = false;
    while (!winner) {
        playRound();
        winner = checkWinner();
    }
    if (playerScore > computerScore) {
        cout << "Player wins!" << endl;
    }
    else {
        cout << "Computer wins!" << endl;
    }
}
