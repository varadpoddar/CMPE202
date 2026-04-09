#ifndef NETWORK_GAME_ENGINE_H
#define NETWORK_GAME_ENGINE_H

#include "Choice.h"
#include "ComputerPlayer.h"
#include "NetworkManager.h"

#include <QObject>

// Server-side game engine for network play.
//
// Supports two modes:
//   VS_COMPUTER  — one human client plays against the server's AI
//   VS_PLAYER    — two human clients play against each other (server is referee)
//
// The server starts a game once the required number of clients has joined.
// For VS_COMPUTER, the computer plays using Strategy (Random or Smart).
// For VS_PLAYER, the server waits for both clients' choices then resolves.
//
// Signals fire for each round result so the MainWindow can update its UI.

class NetworkGameEngine : public QObject {
    Q_OBJECT

public:
    enum class GameMode { VS_COMPUTER, VS_PLAYER };

    explicit NetworkGameEngine(QObject* parent = nullptr);
    ~NetworkGameEngine() override = default;

    // Configure before starting
    void setRounds(int n)               { totalRounds = n; }
    void setGameMode(GameMode m)        { gameMode = m; }
    void setUseSmart(bool smart)        { useSmart = smart; }

    // Called once per client connection
    void addClient(NetworkManager* nm, const QString& playerName);

    // Start/reset
    void startGame();
    void reset();

    int getRounds() const    { return totalRounds; }
    GameMode getMode() const { return gameMode; }

signals:
    // Emitted so the hosting window can show live status
    void roundFinished(int round, int totalRounds,
                       Choice p1Choice, Choice p2Choice,
                       int p1Score, int p2Score, int ties);
    void gameFinished(int p1Score, int p2Score, int ties);
    void statusMessage(const QString& msg);

private slots:
    void onClient1Choice(Choice c);
    void onClient2Choice(Choice c);
    void onClientDisconnected();

private:
    void resolveRound();
    void sendRoundStart();

    GameMode gameMode  = GameMode::VS_COMPUTER;
    int  totalRounds   = 10;
    bool useSmart      = false;

    // Current game state
    int currentRound   = 0;
    int p1Score        = 0;
    int p2Score        = 0;
    int ties           = 0;

    // VS_COMPUTER: nm1 is the human client, computer player is internal
    // VS_PLAYER:   nm1 = player 1, nm2 = player 2
    NetworkManager* nm1 = nullptr;
    NetworkManager* nm2 = nullptr;
    QString name1, name2;

    // Pending choices for current round
    bool hasChoice1 = false;
    bool hasChoice2 = false;
    Choice choice1  = Choice::ROCK;
    Choice choice2  = Choice::ROCK;

    std::unique_ptr<ComputerPlayer> computer;  // only used in VS_COMPUTER mode
};

#endif
