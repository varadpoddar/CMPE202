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

    // Not enough human history yet — play randomly
    if (static_cast<int>(history.size()) < prefixLength) {
        lastConfidence = 0;
        lastPrediction = randomChoice();
        return lastPrediction;
    }

    // Build prefix from the last (N-1) human choices
    std::string prefix;
    prefix.reserve(static_cast<std::size_t>(prefixLength));
    int start = static_cast<int>(history.size()) - prefixLength;
    for (int i = start; i < static_cast<int>(history.size()); ++i) {
        prefix.push_back(history[static_cast<std::size_t>(i)]);
    }

    // Find which human choice most frequently followed this prefix
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
        // No data yet for this prefix — play randomly
        lastConfidence = 0;
        lastPrediction = randomChoice();
        return lastPrediction;
    }

    lastConfidence = bestFrequency;
    lastPrediction = tokenToChoice(predictedToken);
    return counterChoice(lastPrediction);
}

Choice SmartStrategy::getLastPrediction() const {
    return lastPrediction;
}

int SmartStrategy::getLastConfidence() const {
    return lastConfidence;
}

void SmartStrategy::updateHistory(Choice humanChoice, Choice /*computerChoice*/) {
    // Only track human choices — computer choices are irrelevant to prediction
    history.push_back(choiceToToken(humanChoice));

    // Keep the last N human choices
    while (static_cast<int>(history.size()) > sequenceLength) {
        history.pop_front();
    }

    // Once we have a full N-length sequence, record it
    if (static_cast<int>(history.size()) == sequenceLength) {
        std::string key(history.begin(), history.end());
        store.increment(key);
    }
}

void SmartStrategy::load() {
    // Do NOT clear history — preserve recent context across games
    store.load();
}

void SmartStrategy::save() {
    store.save();
}

Choice SmartStrategy::randomChoice() {
    int value = distribution(randomEngine);
    if (value == 0) return Choice::ROCK;
    if (value == 1) return Choice::PAPER;
    return Choice::SCISSORS;
}

char SmartStrategy::choiceToToken(Choice choice) const {
    if (choice == Choice::ROCK)  return 'R';
    if (choice == Choice::PAPER) return 'P';
    return 'S';
}

Choice SmartStrategy::tokenToChoice(char token) const {
    if (token == 'R') return Choice::ROCK;
    if (token == 'P') return Choice::PAPER;
    return Choice::SCISSORS;
}

Choice SmartStrategy::counterChoice(Choice predictedHumanChoice) const {
    if (predictedHumanChoice == Choice::ROCK)  return Choice::PAPER;
    if (predictedHumanChoice == Choice::PAPER) return Choice::SCISSORS;
    return Choice::ROCK;
}
