#include "GameEngine.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace {
constexpr int DEFAULT_ROUNDS = 20;

int parseRounds(int argc, char* argv[]) {
    int configuredRounds = DEFAULT_ROUNDS;

    for (int index = 1; index < argc; ++index) {
        std::string argument = argv[index];
        const std::string prefix = "--rounds=";

        if (argument.rfind(prefix, 0) == 0) {
            std::string value = argument.substr(prefix.size());
            try {
                int parsed = std::stoi(value);
                if (parsed > 0) {
                    configuredRounds = parsed;
                } else {
                    std::cout << "Ignoring invalid rounds value: " << value
                              << ". Using default " << DEFAULT_ROUNDS << ".\n";
                    configuredRounds = DEFAULT_ROUNDS;
                }
            } catch (...) {
                std::cout << "Ignoring invalid rounds value: " << value
                          << ". Using default " << DEFAULT_ROUNDS << ".\n";
                configuredRounds = DEFAULT_ROUNDS;
            }
        }
    }

    return configuredRounds;
}
}

int main(int argc, char* argv[]) {
    int rounds = parseRounds(argc, argv);

    HumanPlayer humanPlayer;
    ComputerPlayer computerPlayer;
    GameEngine gameEngine(humanPlayer, computerPlayer, rounds);

    gameEngine.play();
    return 0;
}
