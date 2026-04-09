#ifndef GUI_GAME_ENGINE_H
#define GUI_GAME_ENGINE_H

#include "GameEngine.h"
#include "GUIHumanPlayer.h"

#include <QObject>

// GUI-mode engine. Inherits GameEngine (for game logic) and QObject (for signals/slots).
// Instead of printing to stdout, display methods emit Qt signals that MainWindow connects to.
class GUIGameEngine : public QObject, public GameEngine {
    Q_OBJECT

public:
    GUIGameEngine(GUIHumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds,
                  QObject* parent = nullptr);

    // Called by MainWindow when user clicks a Rock/Paper/Scissors button.
    // Sets the human choice then drives one round.
    void humanChose(Choice c);

    // Called by MainWindow when user clicks "Start Game".
    void startGame(int rounds);

signals:
    void roundResultReady(int round, int totalRounds, RoundResult result,
                          int humanScore, int computerScore, int ties);
    void gameFinished(int humanScore, int computerScore, int ties);

protected:
    void displayGameStart() override;
    void displayRoundHeader(int roundNumber) override;
    void displayRoundResult(int roundNumber, const RoundResult& result) override;
    void displayFinalScore(int hScore, int cScore, int tieCount) override;

private:
    GUIHumanPlayer& guiHumanPlayer;
};

#endif
