#include "HumanPlayer.h"

#include <iostream>
#include <string>

Choice HumanPlayer::getChoice() const {
    while (true) {
        std::cout << "Enter your choice (R/P/S): ";

        std::string input;
        std::getline(std::cin, input);

        if (!std::cin) {
            return Choice::ROCK;
        }

        if (input.empty()) {
            std::cout << "Invalid input. Please enter R, P, or S.\n";
            continue;
        }

        Choice parsedChoice = Choice::ROCK;
        if (parseChoiceChar(input[0], parsedChoice)) {
            return parsedChoice;
        }

        std::cout << "Invalid input. Please enter R, P, or S.\n";
    }
}
