#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Choice.h"
#include "Strategy.h"

#include <memory>

class ComputerPlayer {
public:
    explicit ComputerPlayer(std::unique_ptr<Strategy> strategy);
    Choice getChoice();
    Choice getPrediction() const;
    int    getConfidence() const;
    void updateHistory(Choice humanChoice, Choice computerChoice);
    void load();
    void save();

private:
    std::unique_ptr<Strategy> strategy;
};

#endif
