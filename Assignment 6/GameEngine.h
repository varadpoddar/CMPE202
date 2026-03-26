#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "ComputerPlayer.h"
#include "HumanPlayer.h"

class GameEngine {
public:
    GameEngine(HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds);
    void play();

private:
    HumanPlayer& humanPlayer;
    ComputerPlayer& computerPlayer;
    int rounds;
};

#endif
