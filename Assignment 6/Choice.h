#ifndef CHOICE_H
#define CHOICE_H

#include <string>

enum class Choice {
    ROCK,
    PAPER,
    SCISSORS
};

enum class RoundOutcome {
    HUMAN_WIN,
    COMPUTER_WIN,
    TIE
};

struct RoundResult {
    Choice humanChoice;
    Choice computerChoice;
    RoundOutcome outcome;
};

std::string choiceToString(Choice choice);
bool parseChoiceChar(char input, Choice& outChoice);
RoundOutcome determineOutcome(Choice humanChoice, Choice computerChoice);

#endif
