#include "GameEngine.h"

GameEngine::GameEngine(HumanPlayer& humanPlayerRef, ComputerPlayer& computerPlayerRef, int roundCount)
    : humanPlayer(humanPlayerRef), computerPlayer(computerPlayerRef), rounds(roundCount) {}

// --- Text mode: synchronous loop ---

void GameEngine::playGame() {
    humanScore    = 0;
    computerScore = 0;
    ties          = 0;
    currentRound  = 0;

    computerPlayer.load();
    displayGameStart();

    for (int round = 1; round <= rounds; ++round) {
        currentRound = round;
        displayRoundHeader(round);
        RoundResult result = playRound();
        applyRoundResult(result);
        displayRoundResult(round, result);
    }

    displayFinalScore(humanScore, computerScore, ties);
    computerPlayer.save();
}

// --- GUI mode: event-driven ---

void GameEngine::initGame() {
    humanScore    = 0;
    computerScore = 0;
    ties          = 0;
    currentRound  = 0;

    computerPlayer.load();
    displayGameStart();
}

RoundResult GameEngine::playNextRound() {
    ++currentRound;
    displayRoundHeader(currentRound);
    RoundResult result = playRound();
    applyRoundResult(result);
    displayRoundResult(currentRound, result);

    if (isGameOver()) {
        displayFinalScore(humanScore, computerScore, ties);
        computerPlayer.save();
    }

    return result;
}

bool GameEngine::isGameOver() const {
    return currentRound >= rounds;
}

// --- Shared ---

RoundResult GameEngine::playRound() {
    Choice humanChoice    = humanPlayer.getChoice();
    Choice computerChoice = computerPlayer.getChoice();
    Choice prediction     = computerPlayer.getPrediction();
    int    confidence     = computerPlayer.getConfidence();
    computerPlayer.updateHistory(humanChoice, computerChoice);

    RoundResult result;
    result.humanChoice          = humanChoice;
    result.computerPrediction   = prediction;
    result.computerChoice       = computerChoice;
    result.outcome              = determineOutcome(humanChoice, computerChoice);
    result.predictionConfidence = confidence;
    return result;
}

void GameEngine::applyRoundResult(const RoundResult& result) {
    if (result.outcome == RoundOutcome::HUMAN_WIN) {
        ++humanScore;
    } else if (result.outcome == RoundOutcome::COMPUTER_WIN) {
        ++computerScore;
    } else {
        ++ties;
    }
}
