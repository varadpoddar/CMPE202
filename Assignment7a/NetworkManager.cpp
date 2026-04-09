#include "NetworkManager.h"

#include <QHostAddress>
#include <QNetworkInterface>

NetworkManager::NetworkManager(QObject* parent) : QObject(parent) {}

NetworkManager::~NetworkManager() {
    stopServer();
    disconnectFromServer();
}

// ── Server side ──────────────────────────────────────────────────────────────

bool NetworkManager::startServer(quint16 port) {
    currentRole = Role::Server;
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        currentRole = Role::None;
        return false;
    }
    return true;
}

void NetworkManager::stopServer() {
    if (tcpServer) {
        tcpServer->close();
        tcpServer->deleteLater();
        tcpServer = nullptr;
    }
    if (clientSocket) {
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
        clientSocket = nullptr;
    }
}

QString NetworkManager::localAddress() const {
    for (const QNetworkInterface& iface : QNetworkInterface::allInterfaces()) {
        if (iface.flags() & QNetworkInterface::IsLoopBack) continue;
        if (!(iface.flags() & QNetworkInterface::IsUp)) continue;
        for (const QNetworkAddressEntry& entry : iface.addressEntries()) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                return entry.ip().toString();
        }
    }
    return "127.0.0.1";
}

quint16 NetworkManager::serverPort() const {
    return tcpServer ? tcpServer->serverPort() : 0;
}

bool NetworkManager::hasClient() const {
    return clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState;
}

void NetworkManager::onNewConnection() {
    if (!tcpServer) return;
    QTcpSocket* socket = tcpServer->nextPendingConnection();
    if (!socket) return;

    if (clientSocket) {
        // Already have one client — reject
        socket->disconnectFromHost();
        socket->deleteLater();
        return;
    }

    clientSocket = socket;
    connect(clientSocket, &QTcpSocket::readyRead,    this, &NetworkManager::onClientDataReady);
    connect(clientSocket, &QTcpSocket::disconnected, this, &NetworkManager::onClientSocketDisconnected);
    connect(clientSocket, &QAbstractSocket::errorOccurred, this, &NetworkManager::onSocketError);
}

void NetworkManager::onClientDataReady() {
    clientBuffer += QString::fromUtf8(clientSocket->readAll());
    int pos;
    while ((pos = clientBuffer.indexOf('\n')) != -1) {
        QString msg = clientBuffer.left(pos).trimmed();
        clientBuffer = clientBuffer.mid(pos + 1);
        if (!msg.isEmpty())
            processClientMessage(msg);
    }
}

void NetworkManager::onClientSocketDisconnected() {
    if (clientSocket) {
        clientSocket->deleteLater();
        clientSocket = nullptr;
    }
    emit clientDisconnected();
}

// Parses messages arriving at the server (sent by the client)
void NetworkManager::processClientMessage(const QString& message) {
    if (message.startsWith("JOIN:")) {
        remoteName = message.mid(5);
        emit clientConnected(remoteName);
    } else if (message.startsWith("CHOICE:")) {
        QString token = message.mid(7);
        if (!token.isEmpty())
            emit opponentChoseReceived(charToChoice(token[0].toLatin1()));
    }
}

void NetworkManager::sendToClient(const QString& message) {
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState)
        clientSocket->write((message + "\n").toUtf8());
}

// ── Client side ──────────────────────────────────────────────────────────────

void NetworkManager::connectToServer(const QString& host, quint16 port, const QString& playerName) {
    currentRole = Role::Client;
    localName   = playerName;

    serverSocket = new QTcpSocket(this);
    connect(serverSocket, &QTcpSocket::readyRead,    this, &NetworkManager::onServerDataReady);
    connect(serverSocket, &QTcpSocket::disconnected, this, &NetworkManager::onServerSocketDisconnected);
    connect(serverSocket, &QAbstractSocket::errorOccurred, this, &NetworkManager::onSocketError);
    connect(serverSocket, &QTcpSocket::connected, this, [this]() {
        sendToServer("JOIN:" + localName);
    });

    serverSocket->connectToHost(host, port);
}

void NetworkManager::disconnectFromServer() {
    if (serverSocket) {
        serverSocket->disconnectFromHost();
        serverSocket->deleteLater();
        serverSocket = nullptr;
    }
}

void NetworkManager::onServerDataReady() {
    serverBuffer += QString::fromUtf8(serverSocket->readAll());
    int pos;
    while ((pos = serverBuffer.indexOf('\n')) != -1) {
        QString msg = serverBuffer.left(pos).trimmed();
        serverBuffer = serverBuffer.mid(pos + 1);
        if (!msg.isEmpty())
            processServerMessage(msg);
    }
}

void NetworkManager::onServerSocketDisconnected() {
    if (serverSocket) {
        serverSocket->deleteLater();
        serverSocket = nullptr;
    }
    emit disconnectedFromServer();
}

// Parses messages arriving at the client (sent by the server)
void NetworkManager::processServerMessage(const QString& message) {
    if (message.startsWith("WELCOME:")) {
        remoteName = message.mid(8);
        emit connectedToServer(remoteName);

    } else if (message.startsWith("GAME_START:")) {
        // GAME_START:<rounds>:<RANDOM|SMART>
        QStringList parts = message.mid(11).split(':');
        if (parts.size() >= 2) {
            int rounds  = parts[0].toInt();
            bool isSmart = (parts[1] == "SMART");
            emit gameStartReceived(rounds, isSmart);
        }

    } else if (message.startsWith("ROUND_START:")) {
        int roundNum = message.mid(12).toInt();
        emit roundStartReceived(roundNum);

    } else if (message.startsWith("RESULT:")) {
        // RESULT:<clientChoice>:<serverChoice>:<outcome>:<clientScore>:<serverScore>:<ties>
        QStringList parts = message.mid(7).split(':');
        if (parts.size() >= 6) {
            Choice clientChoice = charToChoice(parts[0][0].toLatin1());
            Choice serverChoice = charToChoice(parts[1][0].toLatin1());
            int clientScore = parts[3].toInt();
            int serverScore = parts[4].toInt();
            int ties        = parts[5].toInt();
            emit resultReceived(clientChoice, serverChoice, clientScore, serverScore, ties);
        }

    } else if (message.startsWith("GAME_OVER:")) {
        QStringList parts = message.mid(10).split(':');
        if (parts.size() >= 3) {
            emit gameOverReceived(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
        }
    }
}

void NetworkManager::sendToServer(const QString& message) {
    if (serverSocket && serverSocket->state() == QAbstractSocket::ConnectedState)
        serverSocket->write((message + "\n").toUtf8());
}

// ── Send helpers (server → client) ───────────────────────────────────────────

void NetworkManager::sendWelcome(const QString& serverName) {
    sendToClient("WELCOME:" + serverName);
}

void NetworkManager::sendGameStart(int rounds, bool isSmart) {
    sendToClient(QString("GAME_START:%1:%2").arg(rounds).arg(isSmart ? "SMART" : "RANDOM"));
}

void NetworkManager::sendRoundStart(int roundNum) {
    sendToClient(QString("ROUND_START:%1").arg(roundNum));
}

void NetworkManager::sendResult(Choice clientChoice, Choice serverChoice,
                                int clientScore, int serverScore, int ties) {
    // outcome from client's perspective
    QString outcome;
    if (clientChoice == serverChoice) outcome = "TIE";
    else {
        bool clientWins = (clientChoice == Choice::ROCK     && serverChoice == Choice::SCISSORS) ||
                          (clientChoice == Choice::SCISSORS && serverChoice == Choice::PAPER)    ||
                          (clientChoice == Choice::PAPER    && serverChoice == Choice::ROCK);
        outcome = clientWins ? "WIN" : "LOSE";
    }
    sendToClient(QString("RESULT:%1:%2:%3:%4:%5:%6")
        .arg(choiceToChar(clientChoice))
        .arg(choiceToChar(serverChoice))
        .arg(outcome)
        .arg(clientScore)
        .arg(serverScore)
        .arg(ties));
}

void NetworkManager::sendGameOver(int clientScore, int serverScore, int ties) {
    sendToClient(QString("GAME_OVER:%1:%2:%3").arg(clientScore).arg(serverScore).arg(ties));
}

// ── Client → server ───────────────────────────────────────────────────────────

void NetworkManager::sendChoice(Choice c) {
    sendToServer(QString("CHOICE:%1").arg(choiceToChar(c)));
}

// ── Error handling ────────────────────────────────────────────────────────────

void NetworkManager::onSocketError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
    QAbstractSocket* sock = qobject_cast<QAbstractSocket*>(sender());
    if (!sock) return;

    if (sock == serverSocket) {
        emit connectionFailed(sock->errorString());
    }
    // client socket errors are handled via disconnected signal
}

// ── Utility ───────────────────────────────────────────────────────────────────

char NetworkManager::choiceToChar(Choice c) {
    switch (c) {
        case Choice::ROCK:     return 'R';
        case Choice::PAPER:    return 'P';
        case Choice::SCISSORS: return 'S';
        default:               return '?';
    }
}

Choice NetworkManager::charToChoice(char c) {
    switch (c) {
        case 'R': return Choice::ROCK;
        case 'P': return Choice::PAPER;
        case 'S': return Choice::SCISSORS;
        default:  return Choice::ROCK;
    }
}
