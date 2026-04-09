#ifndef GUI_HUMAN_PLAYER_H
#define GUI_HUMAN_PLAYER_H

#include "Choice.h"
#include "HumanPlayer.h"

// GUI-mode override of HumanPlayer.
// Encapsulates user input as button clicks rather than blocking std::cin.
// MainWindow calls setChoice() when the user clicks Rock/Paper/Scissors,
// then the game engine calls getChoice() to retrieve it — no blocking I/O.
class GUIHumanPlayer : public HumanPlayer {
public:
    GUIHumanPlayer();

    void setChoice(Choice c);
    Choice getChoice() const override;

private:
    Choice pendingChoice;
};

#endif
