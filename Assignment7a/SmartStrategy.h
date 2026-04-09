#ifndef SMART_STRATEGY_H
#define SMART_STRATEGY_H

#include "FrequencyStore.h"
#include "Strategy.h"

#include <deque>
#include <random>
#include <string>

class SmartStrategy : public Strategy {
public:
    explicit SmartStrategy(int sequenceLength = 3, std::string filePath = "frequencies.dat");

    Choice getChoice() override;
    Choice getLastPrediction() const override;
    int getLastConfidence() const override;
    void updateHistory(Choice humanChoice, Choice computerChoice) override;
    void load() override;
    void save() override;

private:
    int sequenceLength;
    FrequencyStore store;
    std::deque<char> history;
    Choice lastPrediction  = Choice::ROCK;
    int    lastConfidence  = 0;

    std::mt19937 randomEngine;
    std::uniform_int_distribution<int> distribution;

    Choice randomChoice();
    char choiceToToken(Choice choice) const;
    Choice tokenToChoice(char token) const;
    Choice counterChoice(Choice predictedHumanChoice) const;
};

#endif