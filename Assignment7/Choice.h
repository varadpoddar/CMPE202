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
    Choice computerPrediction;
    Choice computerChoice;
    RoundOutcome outcome;
    int predictionConfidence = 0;  // frequency count behind the prediction (0 = random guess)
};

std::string choiceToString(Choice choice);
bool parseChoiceChar(char input, Choice& outChoice);
RoundOutcome determineOutcome(Choice humanChoice, Choice computerChoice);

#endif
