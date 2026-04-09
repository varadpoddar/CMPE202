#ifndef RANDOM_STRATEGY_H
#define RANDOM_STRATEGY_H

#include "Strategy.h"

#include <random>

class RandomStrategy : public Strategy {
public:
    RandomStrategy();

    Choice getChoice() override;
    void updateHistory(Choice humanChoice, Choice computerChoice) override;

private:
    std::mt19937 randomEngine;
    std::uniform_int_distribution<int> distribution;
};

#endif