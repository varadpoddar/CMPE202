#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Choice.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

class GameEngine {
public:
    GameEngine(HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds);
    virtual ~GameEngine() = default;

    // Text mode: runs all rounds synchronously
    void playGame();

    // GUI mode: event-driven; call initGame() once, then playNextRound() per user action
    void initGame();
    RoundResult playNextRound();
    bool isGameOver() const;

    int getCurrentRound() const  { return currentRound; }
    int getHumanScore() const    { return humanScore; }
    int getComputerScore() const { return computerScore; }
    int getTies() const          { return ties; }

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
    int currentRound  = 0;
    int humanScore    = 0;
    int computerScore = 0;
    int ties          = 0;

    void applyRoundResult(const RoundResult& result);
};

#endif
