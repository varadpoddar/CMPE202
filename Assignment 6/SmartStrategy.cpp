#include "SmartStrategy.h"

#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

SmartStrategy::SmartStrategy(int sequenceLengthValue, std::string filePath)
    : sequenceLength(sequenceLengthValue < 2 ? 2 : sequenceLengthValue),
      store(std::move(filePath)),
      randomEngine(static_cast<unsigned int>(
          std::chrono::high_resolution_clock::now().time_since_epoch().count())),
      distribution(0, 2) {}

Choice SmartStrategy::getChoice() {
    const int prefixLength = sequenceLength - 1;
    if (static_cast<int>(history.size()) < prefixLength) {
        return randomChoice();
    }

    std::string prefix;
    prefix.reserve(static_cast<std::size_t>(prefixLength));
    for (int index = static_cast<int>(history.size()) - prefixLength;
         index < static_cast<int>(history.size());
         ++index) {
        prefix.push_back(history[static_cast<std::size_t>(index)]);
    }

    std::vector<char> candidates = {'R', 'P', 'S'};
    std::shuffle(candidates.begin(), candidates.end(), randomEngine);

    int bestFrequency = 0;
    char predictedToken = '\0';
    for (char token : candidates) {
        int frequency = store.getFrequency(prefix + token);
        if (frequency > bestFrequency) {
            bestFrequency = frequency;
            predictedToken = token;
        }
    }

    if (bestFrequency == 0 || predictedToken == '\0') {
        return randomChoice();
    }

    return counterChoice(tokenToChoice(predictedToken));
}

void SmartStrategy::updateHistory(Choice humanChoice, Choice computerChoice) {
    // Record computer then human so stored sequences end with the human's choice.
    // This aligns with getChoice() which looks up sequences by predicting the next human move.
    history.push_back(choiceToToken(computerChoice));
    history.push_back(choiceToToken(humanChoice));

    while (static_cast<int>(history.size()) > sequenceLength) {
        history.pop_front();
    }

    if (static_cast<int>(history.size()) == sequenceLength) {
        std::string key(history.begin(), history.end());
        store.increment(key);
    }
}

void SmartStrategy::load() {
    history.clear();
    store.load();
}

void SmartStrategy::save() {
    store.save();
}

Choice SmartStrategy::randomChoice() {
    int value = distribution(randomEngine);
    if (value == 0) {
        return Choice::ROCK;
    }

    if (value == 1) {
        return Choice::PAPER;
    }

    return Choice::SCISSORS;
}

char SmartStrategy::choiceToToken(Choice choice) const {
    if (choice == Choice::ROCK) {
        return 'R';
    }

    if (choice == Choice::PAPER) {
        return 'P';
    }

    return 'S';
}

Choice SmartStrategy::tokenToChoice(char token) const {
    if (token == 'R') {
        return Choice::ROCK;
    }

    if (token == 'P') {
        return Choice::PAPER;
    }

    return Choice::SCISSORS;
}

Choice SmartStrategy::counterChoice(Choice predictedHumanChoice) const {
    if (predictedHumanChoice == Choice::ROCK) {
        return Choice::PAPER;
    }

    if (predictedHumanChoice == Choice::PAPER) {
        return Choice::SCISSORS;
    }

    return Choice::ROCK;
}