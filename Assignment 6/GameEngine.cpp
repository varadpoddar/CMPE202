#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine(HumanPlayer& humanPlayerRef, ComputerPlayer& computerPlayerRef, int roundCount)
    : humanPlayer(humanPlayerRef), computerPlayer(computerPlayerRef), rounds(roundCount) {}

void GameEngine::play() {
    int humanScore = 0;
    int computerScore = 0;
    int ties = 0;

    std::cout << "Starting Rock-Paper-Scissors for " << rounds << " rounds.\n\n";

    for (int round = 1; round <= rounds; ++round) {
        std::cout << "Round " << round << " / " << rounds << "\n";

        Choice humanChoice = humanPlayer.getChoice();
        Choice computerChoice = computerPlayer.getChoice();
        RoundOutcome outcome = determineOutcome(humanChoice, computerChoice);

        std::cout << "You: " << choiceToString(humanChoice)
                  << " | Computer: " << choiceToString(computerChoice) << "\n";

        if (outcome == RoundOutcome::HUMAN_WIN) {
            ++humanScore;
            std::cout << "Result: Human wins this round.\n\n";
        } else if (outcome == RoundOutcome::COMPUTER_WIN) {
            ++computerScore;
            std::cout << "Result: Computer wins this round.\n\n";
        } else {
            ++ties;
            std::cout << "Result: Tie.\n\n";
        }
    }

    std::cout << "Final Score after " << rounds << " rounds:\n";
    std::cout << "Human: " << humanScore << "\n";
    std::cout << "Computer: " << computerScore << "\n";
    std::cout << "Ties: " << ties << "\n";
}
