#include "GameEngine.h"

GameEngine::GameEngine(HumanPlayer& humanPlayerRef, ComputerPlayer& computerPlayerRef, int roundCount)
    : humanPlayer(humanPlayerRef), computerPlayer(computerPlayerRef), rounds(roundCount), humanScore(0), computerScore(0), ties(0) {}

void GameEngine::playGame() {
    humanScore = 0;
    computerScore = 0;
    ties = 0;

    computerPlayer.load();

    displayGameStart();

    for (int round = 1; round <= rounds; ++round) {
        displayRoundHeader(round);
        RoundResult result = playRound();
        applyRoundResult(result);
        displayRoundResult(round, result);
    }

    displayFinalScore(humanScore, computerScore, ties);

    computerPlayer.save();
}

RoundResult GameEngine::playRound() {
    Choice humanChoice = humanPlayer.getChoice();
    Choice computerChoice = computerPlayer.getChoice();
    computerPlayer.updateHistory(humanChoice, computerChoice);

    RoundResult result;
    result.humanChoice = humanChoice;
    result.computerChoice = computerChoice;
    result.outcome = determineOutcome(humanChoice, computerChoice);
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
