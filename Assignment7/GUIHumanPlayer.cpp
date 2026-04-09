#include "GUIHumanPlayer.h"

GUIHumanPlayer::GUIHumanPlayer() : pendingChoice(Choice::ROCK) {}

void GUIHumanPlayer::setChoice(Choice c) {
    pendingChoice = c;
}

Choice GUIHumanPlayer::getChoice() const {
    return pendingChoice;
}
