#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Choice.h"

// Encapsulates how the human player provides input.
// getChoice() is virtual so subclasses can override the input mechanism
// without changing the game engine — e.g. GUIHumanPlayer uses button
// clicks instead of blocking on std::cin.
class HumanPlayer {
public:
    virtual ~HumanPlayer() = default;
    virtual Choice getChoice() const;
};

#endif
