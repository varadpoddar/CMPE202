#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(std::unique_ptr<Strategy> strategyPtr)
    : strategy(std::move(strategyPtr)) {}

Choice ComputerPlayer::getChoice() {
    if (!strategy) {
        return Choice::ROCK;
    }

    return strategy->getChoice();
}

void ComputerPlayer::updateHistory(Choice humanChoice, Choice computerChoice) {
    if (strategy) {
        strategy->updateHistory(humanChoice, computerChoice);
    }
}

void ComputerPlayer::load() {
    if (strategy) {
        strategy->load();
    }
}

void ComputerPlayer::save() {
    if (strategy) {
        strategy->save();
    }
}
