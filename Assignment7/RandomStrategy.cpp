#include "RandomStrategy.h"

#include <chrono>

RandomStrategy::RandomStrategy()
    : randomEngine(static_cast<unsigned int>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      distribution(0, 2) {}

Choice RandomStrategy::getChoice() {
    int value = distribution(randomEngine);

    if (value == 0) {
        return Choice::ROCK;
    }

    if (value == 1) {
        return Choice::PAPER;
    }

    return Choice::SCISSORS;
}

void RandomStrategy::updateHistory(Choice, Choice) {
    // Random strategy ignores round history.
}