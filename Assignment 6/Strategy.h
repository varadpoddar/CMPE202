#ifndef STRATEGY_H
#define STRATEGY_H

#include "Choice.h"

class Strategy {
public:
    virtual ~Strategy() = default;

    virtual Choice getChoice() = 0;
    virtual void updateHistory(Choice humanChoice, Choice computerChoice) = 0;
    virtual void load() {}
    virtual void save() {}
};

#endif