#include "Choice.h"

#include <cctype>

std::string choiceToString(Choice choice) {
    switch (choice) {
        case Choice::ROCK:
            return "Rock";
        case Choice::PAPER:
            return "Paper";
        case Choice::SCISSORS:
            return "Scissors";
    }

    return "Unknown";
}

bool parseChoiceChar(char input, Choice& outChoice) {
    char normalized = static_cast<char>(std::toupper(static_cast<unsigned char>(input)));

    if (normalized == 'R') {
        outChoice = Choice::ROCK;
        return true;
    }

    if (normalized == 'P') {
        outChoice = Choice::PAPER;
        return true;
    }

    if (normalized == 'S') {
        outChoice = Choice::SCISSORS;
        return true;
    }

    return false;
}

RoundOutcome determineOutcome(Choice humanChoice, Choice computerChoice) {
    if (humanChoice == computerChoice) {
        return RoundOutcome::TIE;
    }

    if ((humanChoice == Choice::ROCK && computerChoice == Choice::SCISSORS) ||
        (humanChoice == Choice::SCISSORS && computerChoice == Choice::PAPER) ||
        (humanChoice == Choice::PAPER && computerChoice == Choice::ROCK)) {
        return RoundOutcome::HUMAN_WIN;
    }

    return RoundOutcome::COMPUTER_WIN;
}
