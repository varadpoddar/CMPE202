#include "ConsoleGameEngine.h"

#include <iostream>

ConsoleGameEngine::ConsoleGameEngine(HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, int rounds)
    : GameEngine(humanPlayer, computerPlayer, rounds) {}

void ConsoleGameEngine::displayGameStart() {
    std::cout << "Starting Rock-Paper-Scissors game.\n\n";
}

void ConsoleGameEngine::displayRoundHeader(int roundNumber) {
    std::cout << "Round " << roundNumber << "\n";
}

void ConsoleGameEngine::displayRoundResult(int, const RoundResult& result) {
    std::cout << "You chose:          " << choiceToString(result.humanChoice) << "\n";

    std::string predStr = choiceToString(result.computerPrediction);
    if (result.predictionConfidence > 0) {
        predStr += " (freq: " + std::to_string(result.predictionConfidence) + ")";
    } else {
        predStr += " (random guess)";
    }
    std::cout << "Computer predicted: " << predStr << "\n";
    std::cout << "Computer chose:     " << choiceToString(result.computerChoice) << "\n";

    if (result.outcome == RoundOutcome::HUMAN_WIN) {
        std::cout << "Result: Human wins this round.\n\n";
    } else if (result.outcome == RoundOutcome::COMPUTER_WIN) {
        std::cout << "Result: Computer wins this round.\n\n";
    } else {
        std::cout << "Result: Tie.\n\n";
    }
}

void ConsoleGameEngine::displayFinalScore(int humanScore, int computerScore, int ties) {
    std::cout << "Final Score:\n";
    std::cout << "Human: " << humanScore << "\n";
    std::cout << "Computer: " << computerScore << "\n";
    std::cout << "Ties: " << ties << "\n";
}