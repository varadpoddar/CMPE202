#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Choice.h"

#include <random>

class ComputerPlayer {
public:
    ComputerPlayer();
    Choice getChoice();

private:
    std::mt19937 randomEngine;
    std::uniform_int_distribution<int> distribution;
};

#endif
