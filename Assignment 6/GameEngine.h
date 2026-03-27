#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Choice.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

class GameEngine {
public:
    GameEngine(HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds);
    virtual ~GameEngine() = default;

    void playGame();

protected:
    RoundResult playRound();

    virtual void displayGameStart() = 0;
    virtual void displayRoundHeader(int roundNumber) = 0;
    virtual void displayRoundResult(int roundNumber, const RoundResult& result) = 0;
    virtual void displayFinalScore(int humanScore, int computerScore, int ties) = 0;

    HumanPlayer& humanPlayer;
    ComputerPlayer& computerPlayer;
    int rounds;

private:
    int humanScore;
    int computerScore;
    int ties;

    void applyRoundResult(const RoundResult& result);
};

#endif
