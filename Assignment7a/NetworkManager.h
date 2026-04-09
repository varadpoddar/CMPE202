#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "Choice.h"

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>

// Handles all TCP communication for both server and client roles.
// Uses a simple newline-delimited text protocol.
//
// Protocol messages:
//   Client→Server:  JOIN:<name>
//   Server→Client:  WELCOME:<opponentName>
//   Server→Client:  GAME_START:<rounds>:<RANDOM|SMART>
//   Server→Client:  ROUND_START:<roundNum>
//   Client→Server:  CHOICE:<R|P|S>
//   Server→Client:  RESULT:<clientChoice>:<serverChoice>:<outcome>:<clientScore>:<serverScore>:<ties>
//   Server→Client:  GAME_OVER:<clientScore>:<serverScore>:<ties>
//   Either→Either:  CHAT:<message>   (future use)

class NetworkManager : public QObject {
    Q_OBJECT

public:
    enum class Role { None, Server, Client };

    explicit NetworkManager(QObject* parent = nullptr);
    ~NetworkManager();

    // Server: start listening on port
    bool startServer(quint16 port = 12345);
    void stopServer();
    QString localAddress() const;
    quint16 serverPort() const;
    bool hasClient() const;

    // Client: connect to server
    void connectToServer(const QString& host, quint16 port, const QString& playerName);
    void disconnectFromServer();

    Role role() const { return currentRole; }
    QString playerName() const { return localName; }
    QString opponentName() const { return remoteName; }

    // Send protocol messages
    void sendChoice(Choice c);
    void sendGameStart(int rounds, bool isSmart);    // server → client
    void sendRoundStart(int roundNum);               // server → client
    void sendResult(Choice clientChoice, Choice serverChoice,
                    int clientScore, int serverScore, int ties); // server → client
    void sendGameOver(int clientScore, int serverScore, int ties); // server → client
    void sendWelcome(const QString& serverName);     // server → client

signals:
    // Server signals
    void clientConnected(const QString& clientName);
    void clientDisconnected();

    // Client signals
    void connectedToServer(const QString& serverName);
    void disconnectedFromServer();
    void connectionFailed(const QString& reason);

    // Game protocol signals (both roles)
    void gameStartReceived(int rounds, bool isSmart);
    void roundStartReceived(int roundNum);
    void opponentChoseReceived(Choice c);
    void resultReceived(Choice clientChoice, Choice serverChoice,
                        int clientScore, int serverScore, int ties);
    void gameOverReceived(int clientScore, int serverScore, int ties);

private slots:
    void onNewConnection();
    void onClientDataReady();
    void onServerDataReady();
    void onClientSocketDisconnected();
    void onServerSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);

private:
    Role       currentRole = Role::None;
    QTcpServer* tcpServer  = nullptr;
    QTcpSocket* clientSocket = nullptr;  // server side: connected client
    QTcpSocket* serverSocket = nullptr;  // client side: connection to server

    QString localName;
    QString remoteName;
    QString serverBuffer;
    QString clientBuffer;

    void processServerMessage(const QString& message);
    void processClientMessage(const QString& message);
    void sendToClient(const QString& message);
    void sendToServer(const QString& message);

    static char choiceToChar(Choice c);
    static Choice charToChoice(char c);
};

#endif
