#include "ComputerPlayer.h"

#include <chrono>

ComputerPlayer::ComputerPlayer()
    : randomEngine(static_cast<unsigned int>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      distribution(0, 2) {}

Choice ComputerPlayer::getChoice() {
    int value = distribution(randomEngine);

    if (value == 0) {
        return Choice::ROCK;
    }

    if (value == 1) {
        return Choice::PAPER;
    }

    return Choice::SCISSORS;
}
