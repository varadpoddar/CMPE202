#include "ConsoleGameEngine.h"
#include "MainWindow.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"

#include <QApplication>
#include <iostream>
#include <memory>
#include <string>

namespace {
constexpr int DEFAULT_ROUNDS  = 20;
constexpr int DEFAULT_SMART_N = 5;

struct CliConfig {
    int rounds   = DEFAULT_ROUNDS;
    int smartN   = DEFAULT_SMART_N;
    bool guiMode = false;
    enum class Mode { RANDOM, SMART } mode = Mode::RANDOM;
};

void printUsage(const char* executableName) {
    std::cout << "Usage:\n"
              << "  " << executableName
              << " [--gui] [--random|--smart] [--rounds=<n>] [--n=<n>]\n\n"
              << "  (no args)            Launch Qt GUI mode (default).\n"
              << "  --gui                Launch Qt GUI mode.\n"
              << "  --random             Play with random strategy in text mode.\n"
              << "  --smart              Play with smart strategy in text mode.\n"
              << "  --rounds=<value>     Number of rounds (default 20, text mode only).\n"
              << "  --n=<value>          Smart sequence length N (default 5, with --smart).\n";
}

bool parseCliConfig(int argc, char* argv[], CliConfig& outConfig) {
    bool modeSpecified = false;
    bool nSpecified    = false;

    for (int index = 1; index < argc; ++index) {
        std::string argument = argv[index];

        if (argument == "--gui") {
            outConfig.guiMode = true;
            continue;
        }

        if (argument == "--random") {
            if (modeSpecified && outConfig.mode != CliConfig::Mode::RANDOM) {
                std::cout << "Error: choose either --random or --smart, not both.\n";
                return false;
            }
            outConfig.mode = CliConfig::Mode::RANDOM;
            modeSpecified  = true;
            continue;
        }

        if (argument == "--smart") {
            if (modeSpecified && outConfig.mode != CliConfig::Mode::SMART) {
                std::cout << "Error: choose either --random or --smart, not both.\n";
                return false;
            }
            outConfig.mode = CliConfig::Mode::SMART;
            modeSpecified  = true;
            continue;
        }

        const std::string roundsPrefix = "--rounds=";
        if (argument.rfind(roundsPrefix, 0) == 0) {
            std::string value = argument.substr(roundsPrefix.size());
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

        const std::string nPrefix = "--n=";
        if (argument.rfind(nPrefix, 0) == 0) {
            std::string value = argument.substr(nPrefix.size());
            try {
                int parsed = std::stoi(value);
                if (parsed > 0) {
                    outConfig.smartN = parsed;
                    nSpecified       = true;
                } else {
                    std::cout << "Error: --n must be a positive integer.\n";
                    return false;
                }
            } catch (...) {
                std::cout << "Error: invalid n value '" << value << "'.\n";
                return false;
            }
            continue;
        }

        std::cout << "Error: unknown argument '" << argument << "'.\n";
        return false;
    }

    if (!modeSpecified && !outConfig.guiMode) {
        // No flags given — default to GUI mode.
        // Use --random or --smart explicitly to run in text mode.
        outConfig.guiMode = true;
    }

    if (nSpecified && outConfig.mode != CliConfig::Mode::SMART) {
        std::cout << "Error: --n can only be used with --smart.\n";
        return false;
    }

    return true;
}
} // namespace

int main(int argc, char* argv[]) {
    CliConfig config;
    if (!parseCliConfig(argc, argv, config)) {
        printUsage(argv[0]);
        return 1;
    }

    if (config.guiMode) {
        // GUI mode — Qt owns the event loop
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }

    // Text mode — identical to Assignment 6
    HumanPlayer humanPlayer;

    std::unique_ptr<Strategy> strategy;
    if (config.mode == CliConfig::Mode::RANDOM) {
        strategy = std::make_unique<RandomStrategy>();
    } else {
        strategy = std::make_unique<SmartStrategy>(config.smartN);
    }

    ComputerPlayer computerPlayer(std::move(strategy));
    ConsoleGameEngine gameEngine(humanPlayer, computerPlayer, config.rounds);
    gameEngine.playGame();
    return 0;
}
