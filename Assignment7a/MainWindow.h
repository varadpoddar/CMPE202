#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Choice.h"
#include "ComputerPlayer.h"
#include "GUIGameEngine.h"
#include "GUIHumanPlayer.h"
#include "NetworkGameEngine.h"
#include "NetworkManager.h"
#include "RandomStrategy.h"
#include "SmartStrategy.h"

#include <QMainWindow>
#include <QPixmap>
#include <QVBoxLayout>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // Local game
    void onStartClicked();
    void onResetLearningClicked();
    void onViewDataClicked();
    void onRockClicked();
    void onPaperClicked();
    void onScissorsClicked();
    void onRoundResultReady(int round, int totalRounds, RoundResult result,
                            int humanScore, int computerScore, int ties);
    void onGameFinished(int humanScore, int computerScore, int ties);

    // Network
    void onHostClicked();
    void onJoinClicked();
    void onDisconnectNetClicked();

    // NetworkManager signals → UI updates (client side)
    void onConnectedToServer(const QString& serverName);
    void onDisconnectedFromServer();
    void onConnectionFailed(const QString& reason);
    void onGameStartReceived(int rounds, bool isSmart);
    void onRoundStartReceived(int roundNum);
    void onNetResultReceived(Choice myChoice, Choice oppChoice,
                             int myScore, int oppScore, int ties);
    void onNetGameOverReceived(int myScore, int oppScore, int ties);

    // Server-side: NetworkGameEngine signals
    void onNetRoundFinished(int round, int total,
                            Choice p1Choice, Choice p2Choice,
                            int p1Score, int p2Score, int ties);
    void onNetGameFinished(int p1Score, int p2Score, int ties);
    void onNetStatusMessage(const QString& msg);

    // Server-side: client joined
    void onClientConnected(const QString& clientName);

private:
    Ui::MainWindow* ui;

    // Local game objects
    std::unique_ptr<GUIHumanPlayer>  humanPlayer;
    std::unique_ptr<ComputerPlayer>  computerPlayer;
    std::unique_ptr<GUIGameEngine>   gameEngine;

    // Network objects
    std::unique_ptr<NetworkManager>    serverNm;   // server's NetworkManager (host role)
    std::unique_ptr<NetworkManager>    serverNm2;  // second client (VS_PLAYER mode)
    std::unique_ptr<NetworkManager>    clientNm;   // client's NetworkManager (join role)
    std::unique_ptr<NetworkGameEngine> netEngine;  // server-side engine

    // Network state
    int  netTotalRounds  = 10;
    int  netCurrentRound = 0;
    bool isNetworkClient = false;  // true when we joined someone else's server

    // Hand images
    QPixmap paperPixmap;
    QPixmap scissorsPixmap;
    QPixmap rockPixmap;

    void loadHandImages();
    QPixmap handPixmap(Choice c) const;
    void setChoiceButtonsEnabled(bool enabled);
    void resetDisplay();
    void clearHistory();
    void addHistoryEntry(int round, RoundResult result);
    void addNetHistoryEntry(int round, Choice myChoice, Choice oppChoice, bool iWon, bool isTie);
    QString outcomeString(RoundOutcome outcome) const;

    void setNetworkControlsEnabled(bool enabled);
    void updateHostIpDisplay();
    void sendNetworkChoice(Choice c);

    QVBoxLayout* historyLayout = nullptr;
};

#endif
