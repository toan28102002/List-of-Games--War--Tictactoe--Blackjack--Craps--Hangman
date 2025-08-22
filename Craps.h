#ifndef CRAPS_H
#define CRAPS_H

class Craps {
public:
    Craps() noexcept;
    void play();

private:
    int rollDice();
    int money;
};

#endif
