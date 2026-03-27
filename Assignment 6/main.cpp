#include "ConsoleGameEngine.h"
#include "RandomStrategy.h"

#include <iostream>
#include <memory>
#include <string>

namespace {
constexpr int DEFAULT_ROUNDS = 20;

struct CliConfig {
    int rounds = DEFAULT_ROUNDS;
    bool useRandom = true;
};

void printUsage(const char* executableName) {
    std::cout << "Usage:\n"
              << "  " << executableName << " --random [--rounds=<positive_int>]\n"
              << "\n"
              << "Note: --smart will be added in a later iteration.\n";
}

bool parseCliConfig(int argc, char* argv[], CliConfig& outConfig) {
    bool modeSpecified = false;

    for (int index = 1; index < argc; ++index) {
        std::string argument = argv[index];
        const std::string prefix = "--rounds=";

        if (argument == "--random") {
            outConfig.useRandom = true;
            modeSpecified = true;
            continue;
        }

        if (argument == "--smart") {
            std::cout << "Error: --smart is not implemented in this iteration yet.\n";
            return false;
        }

        if (argument.rfind(prefix, 0) == 0) {
            std::string value = argument.substr(prefix.size());
            try {
                int parsed = std::stoi(value);
                if (parsed > 0) {
                    outConfig.rounds = parsed;
                } else {
                    std::cout << "Error: --rounds must be a positive integer.\n";
                    return false;
                }
            } catch (...) {
                std::cout << "Error: invalid rounds value '" << value << "'.\n";
                return false;
            }

            continue;
        }

        std::cout << "Error: unknown argument '" << argument << "'.\n";
        return false;
    }

    if (!modeSpecified) {
        std::cout << "No mode specified. Defaulting to --random.\n";
        outConfig.useRandom = true;
    }

    return true;
}
}

int main(int argc, char* argv[]) {
    CliConfig config;
    if (!parseCliConfig(argc, argv, config)) {
        printUsage(argv[0]);
        return 1;
    }

    HumanPlayer humanPlayer;

    std::unique_ptr<Strategy> strategy;
    if (config.useRandom) {
        strategy = std::make_unique<RandomStrategy>();
    }

    ComputerPlayer computerPlayer(std::move(strategy));
    ConsoleGameEngine gameEngine(humanPlayer, computerPlayer, config.rounds);

    gameEngine.playGame();
    return 0;
}
