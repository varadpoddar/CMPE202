#include "GUIGameEngine.h"

GUIGameEngine::GUIGameEngine(GUIHumanPlayer& humanPlayerRef, ComputerPlayer& computerPlayerRef,
                             int roundCount, QObject* parent)
    : QObject(parent)
    , GameEngine(humanPlayerRef, computerPlayerRef, roundCount)
    , guiHumanPlayer(humanPlayerRef) {}

void GUIGameEngine::startGame(int roundCount) {
    rounds = roundCount;
    initGame();
}

void GUIGameEngine::humanChose(Choice c) {
    if (isGameOver()) {
        return;
    }

    guiHumanPlayer.setChoice(c);
    playNextRound();
}

// Display methods are no-ops in GUI mode — signals carry the data to MainWindow.

void GUIGameEngine::displayGameStart() {}

void GUIGameEngine::displayRoundHeader(int /*roundNumber*/) {}

void GUIGameEngine::displayRoundResult(int roundNumber, const RoundResult& result) {
    emit roundResultReady(roundNumber, rounds, result,
                          getHumanScore(), getComputerScore(), getTies());
}

void GUIGameEngine::displayFinalScore(int hScore, int cScore, int tieCount) {
    emit gameFinished(hScore, cScore, tieCount);
}
