#include "NetworkGameEngine.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"

#include <QDebug>

NetworkGameEngine::NetworkGameEngine(QObject* parent) : QObject(parent) {}

void NetworkGameEngine::reset() {
    currentRound = 0;
    p1Score = p2Score = ties = 0;
    hasChoice1 = hasChoice2 = false;
    computer.reset();
}

void NetworkGameEngine::addClient(NetworkManager* nm, const QString& playerName) {
    if (!nm1) {
        nm1 = nm;
        name1 = playerName;
        connect(nm1, &NetworkManager::opponentChoseReceived, this, &NetworkGameEngine::onClient1Choice);
        connect(nm1, &NetworkManager::clientDisconnected,    this, &NetworkGameEngine::onClientDisconnected);
    } else if (!nm2 && gameMode == GameMode::VS_PLAYER) {
        nm2 = nm;
        name2 = playerName;
        connect(nm2, &NetworkManager::opponentChoseReceived, this, &NetworkGameEngine::onClient2Choice);
        connect(nm2, &NetworkManager::clientDisconnected,    this, &NetworkGameEngine::onClientDisconnected);
    }
}

void NetworkGameEngine::startGame() {
    reset();

    if (gameMode == GameMode::VS_COMPUTER) {
        std::unique_ptr<Strategy> strat = useSmart
            ? std::unique_ptr<Strategy>(new SmartStrategy())
            : std::unique_ptr<Strategy>(new RandomStrategy());
        computer = std::make_unique<ComputerPlayer>(std::move(strat));
        computer->load();
        name2 = "Computer";

        // Tell client who they're playing and start game
        if (nm1) {
            nm1->sendWelcome(name2);
            nm1->sendGameStart(totalRounds, useSmart);
        }
    } else {
        // VS_PLAYER — both clients already received WELCOME from addClient logic
        if (nm1) nm1->sendGameStart(totalRounds, false);
        if (nm2) nm2->sendGameStart(totalRounds, false);
    }

    emit statusMessage(QString("Game started: %1 vs %2, %3 rounds").arg(name1, name2).arg(totalRounds));
    sendRoundStart();
}

void NetworkGameEngine::sendRoundStart() {
    if (currentRound >= totalRounds) return;
    ++currentRound;
    hasChoice1 = hasChoice2 = false;

    if (nm1) nm1->sendRoundStart(currentRound);
    if (nm2) nm2->sendRoundStart(currentRound);

    emit statusMessage(QString("Round %1 / %2 — waiting for choices...").arg(currentRound).arg(totalRounds));
}

void NetworkGameEngine::onClient1Choice(Choice c) {
    if (hasChoice1) return;
    choice1 = c;
    hasChoice1 = true;
    emit statusMessage(QString("%1 chose.").arg(name1));

    if (gameMode == GameMode::VS_COMPUTER) {
        // Computer picks immediately
        choice2 = computer->getChoice();
        hasChoice2 = true;
    }

    if (hasChoice1 && hasChoice2)
        resolveRound();
}

void NetworkGameEngine::onClient2Choice(Choice c) {
    if (hasChoice2) return;
    choice2 = c;
    hasChoice2 = true;
    emit statusMessage(QString("%1 chose.").arg(name2));

    if (hasChoice1 && hasChoice2)
        resolveRound();
}

void NetworkGameEngine::resolveRound() {
    // Determine winner from p1's perspective
    bool p1Wins = (choice1 == Choice::ROCK     && choice2 == Choice::SCISSORS) ||
                  (choice1 == Choice::SCISSORS && choice2 == Choice::PAPER)    ||
                  (choice1 == Choice::PAPER    && choice2 == Choice::ROCK);
    bool isTie = (choice1 == choice2);

    if (isTie)       ++ties;
    else if (p1Wins) ++p1Score;
    else             ++p2Score;

    // Update AI history
    if (gameMode == GameMode::VS_COMPUTER && computer) {
        computer->updateHistory(choice1, choice2);
        computer->save();
    }

    // Send RESULT to p1: their choice is choice1, opponent's is choice2
    if (nm1) nm1->sendResult(choice1, choice2, p1Score, p2Score, ties);

    // Send RESULT to p2 (VS_PLAYER only): mirror the choices
    if (nm2) nm2->sendResult(choice2, choice1, p2Score, p1Score, ties);

    emit roundFinished(currentRound, totalRounds, choice1, choice2, p1Score, p2Score, ties);

    if (currentRound >= totalRounds) {
        if (nm1) nm1->sendGameOver(p1Score, p2Score, ties);
        if (nm2) nm2->sendGameOver(p2Score, p1Score, ties);
        emit gameFinished(p1Score, p2Score, ties);
        emit statusMessage(QString("Game over. %1: %2 — %3: %4 — Ties: %5")
            .arg(name1).arg(p1Score).arg(name2).arg(p2Score).arg(ties));
    } else {
        sendRoundStart();
    }
}

void NetworkGameEngine::onClientDisconnected() {
    NetworkManager* who = qobject_cast<NetworkManager*>(sender());
    QString who_name = (who == nm1) ? name1 : name2;
    emit statusMessage(who_name + " disconnected.");
}
