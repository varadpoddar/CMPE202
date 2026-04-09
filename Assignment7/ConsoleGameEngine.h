#ifndef CONSOLE_GAME_ENGINE_H
#define CONSOLE_GAME_ENGINE_H

#include "GameEngine.h"

class ConsoleGameEngine : public GameEngine {
public:
    ConsoleGameEngine(HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds);

protected:
    void displayGameStart() override;
    void displayRoundHeader(int roundNumber) override;
    void displayRoundResult(int roundNumber, const RoundResult& result) override;
    void displayFinalScore(int humanScore, int computerScore, int ties) override;
};

#endif