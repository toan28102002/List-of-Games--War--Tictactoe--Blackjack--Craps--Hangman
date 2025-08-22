#include "Blackjack.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

void printCard(string card, string hidden = "");
int getCardValue(string card);
int getCardValue(const vector<string>& hand);
void dealCards(vector<string>& deck, vector<string>& playerHand, vector<string>& dealerHand);
void playerTurn(vector<string>& deck, vector<string>& playerHand);
void dealerTurn(vector<string>& deck, vector<string>& dealerHand);
void printHand(vector<string> hand, bool hideFirstCard = false);
bool playAgain();

void setConsoleColor(int colorCode) {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
#endif
}

void Blackjack::play() {
    while (true) {
        // Create a deck of 52 cards
        vector<string> deck = {"A♥", "2♥", "3♥", "4♥", "5♥", "6♥", "7♥", "8♥", "9♥", "10♥", "J♥", "Q♥", "K♥",
                               "A♠", "2♠", "3♠", "4♠", "5♠", "6♠", "7♠", "8♠", "9♠", "10♠", "J♠", "Q♠", "K♠",
                               "A♦", "2♦", "3♦", "4♦", "5♦", "6♦", "7♦", "8♦", "9♦", "10♦", "J♦", "Q♦", "K♦",
                               "A♣", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "10♣", "J♣", "Q♣", "K♣"};
        vector<string> playerHand, dealerHand;
        srand(time(0)); // Seed the random number generator

        // Deal cards to player and dealer
        dealCards(deck, playerHand, dealerHand);

        // Player's turn
        playerTurn(deck, playerHand);
        if (getCardValue(playerHand) > 21) {
            cout << "BUST! Dealer wins.\n";
        } else {
            // Dealer's turn
            dealerTurn(deck, dealerHand);
            if (getCardValue(dealerHand) > 21) {
                cout << "BUST! Player wins.\n";
            } else {
                // Compare hands
                int playerTotal = getCardValue(playerHand);
                int dealerTotal = getCardValue(dealerHand);
                if (playerTotal > dealerTotal) {
                    cout << "Player wins!\n";
                } else if (playerTotal < dealerTotal) {
                    cout << "Dealer wins!\n";
                } else {
                    cout << "PUSH(Tie!)\n";
                }
            }
        }

        if (!playAgain()) {
            break;
        }
    }
}
//Just make the card more real
void printCard(string card, string hidden) {
    string suit = card.substr(1);
    string rank = card.substr(0, 1);
    string color = (suit == "♥" || suit == "♦") ? "\033[31m" : "\033[30m";
    if (hidden == "") {
        cout << "+-----+\n";
        cout << "|     |\n";
        cout << "| " << color << rank << suit << "\033[0m |\n";
        cout << "|     |\n";
        cout << "+-----+\n";
    } else {
        if (hidden == "first") {
            cout << "+-----+\n";
            cout << "|     |\n";
            cout << "| " << color << "??" << "\033[0m |\n";
            cout << "|     |\n";
            cout << "+-----+\n";
        } else {
            cout << "+-----+\n";
            cout << "|?????|\n";
            cout << "| ? ? |\n";
            cout << "|?????|\n";
            cout << "+-----+\n";
        }
    }
}

//Set card value
int getCardValue(string card) {
if (card[0] == 'A') {
return 11;
} else if (card[0] == '1' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
return 10;
} else {
return card[0] - '0';
}
}
//Get card value 
int getCardValue(const vector<string>& hand) {
int total = 0;
int numAces = 0;
for (const string& card : hand) {
int value = 0;
if (card[0] == 'A') {
value = 11;
numAces++;
} else if (card[0] == '1' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
value = 10;
} else {
value = card[0] - '0';
}
total += value;
}
while (total > 21 && numAces > 0) {
total -= 10;
numAces--;
}
return total;
}

void dealCards(vector<string>& deck, vector<string>& playerHand, vector<string>& dealerHand) {
for (int i = 0; i < 2; i++) {
// Deal card to player
int randIndex = rand() % deck.size();
playerHand.push_back(deck[randIndex]);
deck.erase(deck.begin() + randIndex);
    // Deal card to dealer
    randIndex = rand() % deck.size();
    dealerHand.push_back(deck[randIndex]);
    deck.erase(deck.begin() + randIndex);
}
}
//Function for player get card and if the hand >21 break if not ask for user want another card!
void playerTurn(vector<string>& deck, vector<string>& playerHand) {
    while (true) {
        cout << "Player's hand:\n";
        printHand(playerHand);
        cout << "Total: " << getCardValue(playerHand) << "\n";
        if (getCardValue(playerHand) > 21) {
            break;
        }
        char choice;
        cout << "Do you want another card? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            int randIndex = rand() % deck.size();
            playerHand.push_back(deck[randIndex]);
            deck.erase(deck.begin() + randIndex);
            if (getCardValue(playerHand.back()) == 11 && getCardValue(playerHand) > 21) {
                playerHand.back() = "1" + playerHand.back().substr(1);
            }
        } else {
            break;
        }
    }
}

// De
void dealerTurn(vector<string>& deck, vector<string>& dealerHand) {
while (getCardValue(dealerHand) <= 17) {
int randIndex = rand() % deck.size();
dealerHand.push_back(deck[randIndex]);
deck.erase(deck.begin() + randIndex);
if (getCardValue(dealerHand.back()) == 11 && getCardValue(dealerHand) > 21) {
dealerHand.back() = "1" + dealerHand.back().substr(1);
}
}
cout << "Dealer's hand:\n";
printHand(dealerHand);
cout << "Total: " << getCardValue(dealerHand) << "\n";
}

void printHand(vector<string> hand, bool hideFirstCard) {
for (int i = 0; i < hand.size(); i++) {
if (i == 0 && hideFirstCard) {
printCard(hand[i], "first");
} else {
printCard(hand[i]);
}
}
}

bool playAgain() {
char choice;
cout << "Do you want to play again? (y/n): ";
cin >> choice;
return choice == 'y';
}

