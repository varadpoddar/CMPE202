#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QFrame>
#include <QHeaderView>
#include <QTableWidget>
#include <QTextStream>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QScrollBar>
#include <QString>
#include <QHostAddress>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadHandImages();
    historyLayout = qobject_cast<QVBoxLayout*>(
        ui->historyContainer->layout());

    connect(ui->startButton,         &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->resetLearningButton, &QPushButton::clicked, this, &MainWindow::onResetLearningClicked);
    connect(ui->viewDataButton,      &QPushButton::clicked, this, &MainWindow::onViewDataClicked);
    connect(ui->rockButton,     &QPushButton::clicked, this, &MainWindow::onRockClicked);
    connect(ui->paperButton,    &QPushButton::clicked, this, &MainWindow::onPaperClicked);
    connect(ui->scissorsButton, &QPushButton::clicked, this, &MainWindow::onScissorsClicked);

    // Network buttons
    connect(ui->hostButton,          &QPushButton::clicked, this, &MainWindow::onHostClicked);
    connect(ui->joinButton,          &QPushButton::clicked, this, &MainWindow::onJoinClicked);
    connect(ui->disconnectNetButton, &QPushButton::clicked, this, &MainWindow::onDisconnectNetClicked);

    updateHostIpDisplay();

    // Set small icons on choice buttons
    const int iconSize = 40;
    ui->rockButton->setIcon(rockPixmap.scaled(iconSize, iconSize,
                             Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->rockButton->setIconSize(QSize(iconSize, iconSize));

    ui->paperButton->setIcon(paperPixmap.scaled(iconSize, iconSize,
                              Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->paperButton->setIconSize(QSize(iconSize, iconSize));

    ui->scissorsButton->setIcon(scissorsPixmap.scaled(iconSize, iconSize,
                                 Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->scissorsButton->setIconSize(QSize(iconSize, iconSize));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadHandImages() {
    rockPixmap     = QPixmap(":/images/rock.jpeg");
    paperPixmap    = QPixmap(":/images/paper.jpeg");
    scissorsPixmap = QPixmap(":/images/scissors.jpeg");

    if (rockPixmap.isNull() || paperPixmap.isNull() || scissorsPixmap.isNull()) {
        qDebug() << "WARNING: one or more hand images failed to load!";
    } else {
        qDebug() << "Hand images loaded successfully.";
    }
}

QPixmap MainWindow::handPixmap(Choice c) const {
    switch (c) {
        case Choice::ROCK:     return rockPixmap;
        case Choice::PAPER:    return paperPixmap;
        case Choice::SCISSORS: return scissorsPixmap;
    }
    return {};
}

void MainWindow::onViewDataClicked() {
    QFile file("frequencies.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Learning Data",
            "No frequency data found yet.\nPlay some rounds with Smart mode first.");
        return;
    }

    // Parse key-count pairs and sort by count descending
    QVector<QPair<QString, int>> entries;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(' ');
        if (parts.size() == 2) {
            entries.append({parts[0], parts[1].toInt()});
        }
    }
    file.close();

    std::sort(entries.begin(), entries.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Build dialog with a table
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Smart Algorithm — Frequency Data");
    dialog->resize(380, 460);
    dialog->setStyleSheet(
        "QDialog { background-color: #2e4a3e; color: #eaf5ec; }"
        "QTableWidget { background-color: #3a6b52; color: #eaf5ec; "
        "               gridline-color: #52b788; border: none; }"
        "QTableWidget::item { padding: 4px; }"
        "QHeaderView::section { background-color: #2d6a4f; color: #95d5b2; "
        "                       font-weight: bold; border: none; padding: 4px; }"
        "QDialogButtonBox QPushButton { background-color: #5cb85c; color: white; "
        "    border-radius: 6px; border: none; padding: 6px 20px; }"
        "QLabel { color: #95d5b2; font-size: 12px; }");

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* info = new QLabel(
        QString("Showing %1 learned sequences (sorted by frequency).\n"
                "Higher frequency = stronger prediction confidence.")
            .arg(entries.size()));
    info->setWordWrap(true);
    layout->addWidget(info);

    QTableWidget* table = new QTableWidget(entries.size(), 3, dialog);
    table->setHorizontalHeaderLabels({"Sequence", "Next predicted", "Frequency"});
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setVisible(false);

    // Decode token chars to choice names
    auto tokenName = [](QChar c) -> QString {
        if (c == 'R') return "Rock";
        if (c == 'P') return "Paper";
        return "Scissors";
    };

    for (int i = 0; i < entries.size(); ++i) {
        const QString& key = entries[i].first;
        int count          = entries[i].second;

        // Sequence = all but last char, next predicted = last char
        QString prefix = key.left(key.length() - 1);
        QChar   last   = key.back();

        // Format prefix as "Rock → Paper → ..."
        QStringList prefixParts;
        for (QChar c : prefix) prefixParts << tokenName(c);
        QString seqText = prefixParts.join(" → ");

        table->setItem(i, 0, new QTableWidgetItem(seqText));
        table->setItem(i, 1, new QTableWidgetItem(tokenName(last)));

        QTableWidgetItem* freqItem = new QTableWidgetItem(QString::number(count));
        freqItem->setTextAlignment(Qt::AlignCenter);
        if (count >= 5)      freqItem->setForeground(QColor("#81c784")); // green — confident
        else if (count >= 2) freqItem->setForeground(QColor("#fff176")); // yellow — learning
        else                 freqItem->setForeground(QColor("#ef9a9a")); // red — sparse
        table->setItem(i, 2, freqItem);
    }

    layout->addWidget(table);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttons, &QDialogButtonBox::rejected, dialog, &QDialog::accept);
    layout->addWidget(buttons);

    dialog->exec();
    delete dialog;
}

void MainWindow::onResetLearningClicked() {
    auto reply = QMessageBox::question(
        this, "Reset Learning",
        "Delete all saved frequency data?\n"
        "The Smart algorithm will start learning from scratch.",
        QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    if (QFile::remove("frequencies.dat")) {
        ui->statusLabel->setText("Learning data reset. Smart algorithm starts fresh.");
    } else {
        ui->statusLabel->setText("No learning data found — already clean.");
    }
}

void MainWindow::onStartClicked() {
    int rounds  = ui->roundsSpinBox->value();
    bool isSmart = (ui->algorithmCombo->currentIndex() == 1);

    humanPlayer = std::make_unique<GUIHumanPlayer>();
    std::unique_ptr<Strategy> strategy;
    if (isSmart) {
        strategy = std::make_unique<SmartStrategy>();
    } else {
        strategy = std::make_unique<RandomStrategy>();
    }
    computerPlayer = std::make_unique<ComputerPlayer>(std::move(strategy));
    gameEngine     = std::make_unique<GUIGameEngine>(*humanPlayer, *computerPlayer, rounds);

    connect(gameEngine.get(), &GUIGameEngine::roundResultReady,
            this, &MainWindow::onRoundResultReady);
    connect(gameEngine.get(), &GUIGameEngine::gameFinished,
            this, &MainWindow::onGameFinished);

    resetDisplay();
    clearHistory();
    ui->startButton->setEnabled(false);
    ui->algorithmCombo->setEnabled(false);
    ui->roundsSpinBox->setEnabled(false);
    ui->roundGroup->setTitle("Round");
    ui->statusLabel->setText("Your turn — pick Rock, Paper, or Scissors!");
    setChoiceButtonsEnabled(true);

    gameEngine->startGame(rounds);
}

void MainWindow::onRockClicked()     { if (gameEngine) gameEngine->humanChose(Choice::ROCK); }
void MainWindow::onPaperClicked()    { if (gameEngine) gameEngine->humanChose(Choice::PAPER); }
void MainWindow::onScissorsClicked() { if (gameEngine) gameEngine->humanChose(Choice::SCISSORS); }

void MainWindow::onRoundResultReady(int round, int totalRounds, RoundResult result,
                                    int humanScore, int computerScore, int ties) {
    ui->roundGroup->setTitle(
        QString("Round  %1 of %2").arg(round).arg(totalRounds));

    ui->roundLabel->setText(QString("%1 / %2").arg(round).arg(totalRounds));
    QString predText = QString::fromStdString(choiceToString(result.computerPrediction));
    if (result.predictionConfidence > 0) {
        predText += QString("  (freq: %1)").arg(result.predictionConfidence);
    } else {
        predText += "  (random guess)";
    }
    ui->predictionLabel->setText(predText);

    // Show hand images
    const int displaySize = 130;
    auto setHand = [&](QLabel* lbl, Choice c) {
        QPixmap px = handPixmap(c);
        if (!px.isNull()) {
            lbl->setPixmap(px.scaled(displaySize, displaySize,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            lbl->setText(QString::fromStdString(choiceToString(c)));
        }
    };
    setHand(ui->humanHandLabel,    result.humanChoice);
    setHand(ui->computerHandLabel, result.computerChoice);

    // Result label with colour
    QString winner = outcomeString(result.outcome);
    ui->winnerLabel->setText(winner);
    if (result.outcome == RoundOutcome::HUMAN_WIN) {
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#b7e4c7;");
        ui->statusLabel->setText("You won that round!");
    } else if (result.outcome == RoundOutcome::COMPUTER_WIN) {
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#f4a261;");
        ui->statusLabel->setText("Computer won that round.");
    } else {
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#95d5b2;");
        ui->statusLabel->setText("It's a tie!");
    }

    ui->humanScoreLabel->setText(QString::number(humanScore));
    ui->computerScoreLabel->setText(QString::number(computerScore));
    ui->tiesLabel->setText(QString::number(ties));

    addHistoryEntry(round, result);
}

void MainWindow::onGameFinished(int humanScore, int computerScore, int ties) {
    setChoiceButtonsEnabled(false);
    ui->statusLabel->setText("Game over! Set up a new game above.");

    QString winner;
    if (humanScore > computerScore)      winner = "You win the game!";
    else if (computerScore > humanScore) winner = "Computer wins the game.";
    else                                  winner = "The game is a tie.";

    QString msg = QString("%1\n\nYou: %2    Computer: %3    Ties: %4")
                      .arg(winner).arg(humanScore).arg(computerScore).arg(ties);
    QMessageBox::information(this, "Game Over", msg);

    ui->startButton->setEnabled(true);
    ui->algorithmCombo->setEnabled(true);
    ui->roundsSpinBox->setEnabled(true);
}

void MainWindow::setChoiceButtonsEnabled(bool enabled) {
    ui->rockButton->setEnabled(enabled);
    ui->paperButton->setEnabled(enabled);
    ui->scissorsButton->setEnabled(enabled);
}

void MainWindow::resetDisplay() {
    ui->humanHandLabel->clear();
    ui->computerHandLabel->clear();
    ui->humanHandLabel->setText("?");
    ui->computerHandLabel->setText("?");
    ui->winnerLabel->setText("—");
    ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#95d5b2;");
    ui->roundLabel->setText("—");
    ui->predictionLabel->setText("—");
    ui->humanScoreLabel->setText("0");
    ui->computerScoreLabel->setText("0");
    ui->tiesLabel->setText("0");
}

void MainWindow::clearHistory() {
    if (!historyLayout) return;
    // Remove all items except the bottom spacer (last item)
    while (historyLayout->count() > 1) {
        QLayoutItem* item = historyLayout->takeAt(0);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
}

void MainWindow::addHistoryEntry(int round, RoundResult result) {
    if (!historyLayout) return;

    const int thumbSize = 44;

    // Card frame
    QFrame* card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2e4a3e; border-radius: 6px;"
        "         border: 1px solid #6aab82; }");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(3);
    cardLayout->setContentsMargins(6, 4, 6, 4);

    // Round number
    QLabel* roundLbl = new QLabel(QString("Round %1").arg(round));
    roundLbl->setAlignment(Qt::AlignCenter);
    roundLbl->setStyleSheet("font-size: 11px; font-weight: bold; color: #a8d5b5; border: none;");
    cardLayout->addWidget(roundLbl);

    // Hands row: human img  vs  computer img
    QHBoxLayout* handsRow = new QHBoxLayout();
    handsRow->setSpacing(4);

    auto makeThumb = [&](Choice c) {
        QLabel* lbl = new QLabel();
        lbl->setFixedSize(thumbSize, thumbSize);
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("background-color: #ffffff; border-radius: 6px; border: 1px solid #a8d5b5;");
        QPixmap px = handPixmap(c);
        if (!px.isNull()) {
            lbl->setPixmap(px.scaled(thumbSize - 4, thumbSize - 4,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            lbl->setText(QString::fromStdString(choiceToString(c)));
            lbl->setStyleSheet(lbl->styleSheet() + "color: #333; font-size: 10px;");
        }
        return lbl;
    };

    handsRow->addWidget(makeThumb(result.humanChoice));

    QLabel* vsLbl = new QLabel("vs");
    vsLbl->setAlignment(Qt::AlignCenter);
    vsLbl->setStyleSheet("font-size: 10px; color: #a8d5b5; border: none;");
    handsRow->addWidget(vsLbl);

    handsRow->addWidget(makeThumb(result.computerChoice));
    cardLayout->addLayout(handsRow);

    // Result
    QLabel* resultLbl = new QLabel(outcomeString(result.outcome));
    resultLbl->setAlignment(Qt::AlignCenter);
    resultLbl->setStyleSheet("font-size: 11px; font-weight: bold; border: none; color: "
        + (result.outcome == RoundOutcome::HUMAN_WIN    ? QString("#81c784;") :
           result.outcome == RoundOutcome::COMPUTER_WIN ? QString("#e57373;") :
                                                          QString("#fff176;")));
    cardLayout->addWidget(resultLbl);

    // Insert before the bottom spacer
    historyLayout->insertWidget(historyLayout->count() - 1, card);

    // Scroll to bottom so newest entry is visible
    ui->historyScrollArea->verticalScrollBar()->setValue(
        ui->historyScrollArea->verticalScrollBar()->maximum());
}

QString MainWindow::outcomeString(RoundOutcome outcome) const {
    switch (outcome) {
        case RoundOutcome::HUMAN_WIN:    return "You Win!";
        case RoundOutcome::COMPUTER_WIN: return "Computer Wins!";
        case RoundOutcome::TIE:          return "Tie!";
    }
    return "—";
}

// ── Network helpers ──────────────────────────────────────────────────────────

void MainWindow::updateHostIpDisplay() {
    // Create a temporary NetworkManager just to read local IP
    NetworkManager tmp;
    ui->hostIpLabel->setText(tmp.localAddress());
}

void MainWindow::setNetworkControlsEnabled(bool enabled) {
    ui->hostButton->setEnabled(enabled);
    ui->joinButton->setEnabled(enabled);
    ui->hostPortSpinBox->setEnabled(enabled);
    ui->netModeCombo->setEnabled(enabled);
    ui->netRoundsSpinBox->setEnabled(enabled);
    ui->joinIpEdit->setEnabled(enabled);
    ui->joinPortSpinBox->setEnabled(enabled);
    ui->joinNameEdit->setEnabled(enabled);
    ui->disconnectNetButton->setEnabled(!enabled);
}

// ── Host side ────────────────────────────────────────────────────────────────

void MainWindow::onHostClicked() {
    quint16 port     = static_cast<quint16>(ui->hostPortSpinBox->value());
    int     rounds   = ui->netRoundsSpinBox->value();
    bool    vsPlayer = (ui->netModeCombo->currentIndex() == 1);

    serverNm = std::make_unique<NetworkManager>(this);
    serverNm->setObjectName("serverNm1");

    if (!serverNm->startServer(port)) {
        QMessageBox::critical(this, "Host Error",
            "Could not start server on port " + QString::number(port) + ".\n"
            "Port may already be in use.");
        serverNm.reset();
        return;
    }

    netEngine = std::make_unique<NetworkGameEngine>(this);
    netEngine->setRounds(rounds);
    netEngine->setGameMode(vsPlayer ? NetworkGameEngine::GameMode::VS_PLAYER
                                    : NetworkGameEngine::GameMode::VS_COMPUTER);
    netEngine->setUseSmart(ui->algorithmCombo->currentIndex() == 1);

    connect(netEngine.get(), &NetworkGameEngine::roundFinished,
            this, &MainWindow::onNetRoundFinished);
    connect(netEngine.get(), &NetworkGameEngine::gameFinished,
            this, &MainWindow::onNetGameFinished);
    connect(netEngine.get(), &NetworkGameEngine::statusMessage,
            this, &MainWindow::onNetStatusMessage);
    connect(serverNm.get(), &NetworkManager::clientConnected,
            this, &MainWindow::onClientConnected);

    if (vsPlayer) {
        // Need two clients — set up second listener on same port (same server)
        serverNm2 = std::make_unique<NetworkManager>(this);
        serverNm2->setObjectName("serverNm2");
        // Re-use same QTcpServer: handled inside NetworkManager by accepting second connection.
        // For simplicity, we track second client via same NetworkManager's second pending connection.
        // Actually our NetworkManager only accepts one client per instance.
        // Start a second NetworkManager on a different internal port is complex.
        // Simpler: use a single QTcpServer that queues 2 connections — refactor not needed here
        // because NetworkGameEngine::addClient() is called per accepted connection.
        // For VS_PLAYER, the host also acts as a server waiting for 2 connections.
        // We'll start a second NetworkManager on port+1 for the second player.
        serverNm2->startServer(port + 1);
        connect(serverNm2.get(), &NetworkManager::clientConnected,
                this, &MainWindow::onClientConnected);
        ui->netStatusLabel->setText(
            QString("Hosting: P1 → port %1  |  P2 → port %2  |  Waiting for players...")
                .arg(port).arg(port + 1));
    } else {
        ui->netStatusLabel->setText(
            QString("Hosting on port %1. Waiting for 1 player to join...").arg(port));
    }

    setNetworkControlsEnabled(false);
    isNetworkClient = false;
}

void MainWindow::onClientConnected(const QString& clientName) {
    NetworkManager* who = qobject_cast<NetworkManager*>(sender());
    netEngine->addClient(who, clientName);

    bool vsPlayer = (netEngine->getMode() == NetworkGameEngine::GameMode::VS_PLAYER);

    if (!vsPlayer) {
        // vs Computer — 1 client needed
        ui->netStatusLabel->setText(
            QString("%1 joined! Starting game...").arg(clientName));
        who->sendWelcome("Computer");
        netEngine->startGame();
        // Show the game UI
        resetDisplay();
        clearHistory();
        ui->humanNameLabel->setText(clientName);
        ui->computerNameLabel->setText("Computer (server)");
        ui->statusLabel->setText("Hosting network game — watching rounds live.");
    } else {
        // vs Player — need 2 clients
        static int joinedCount = 0;
        ++joinedCount;
        if (joinedCount == 1) {
            ui->netStatusLabel->setText(
                QString("%1 joined! Waiting for second player...").arg(clientName));
        } else if (joinedCount >= 2) {
            joinedCount = 0;
            ui->netStatusLabel->setText("Both players joined! Starting game...");
            netEngine->startGame();
            resetDisplay();
            clearHistory();
            ui->statusLabel->setText("Hosting network game — watching rounds live.");
        }
    }
}

// Server-side: round/game updates for live display on host window
void MainWindow::onNetRoundFinished(int round, int total,
                                    Choice p1Choice, Choice p2Choice,
                                    int p1Score, int p2Score, int ties) {
    ui->roundGroup->setTitle(QString("Round  %1 of %2").arg(round).arg(total));
    ui->roundLabel->setText(QString("%1 / %2").arg(round).arg(total));

    const int displaySize = 130;
    auto setHand = [&](QLabel* lbl, Choice c) {
        QPixmap px = handPixmap(c);
        if (!px.isNull())
            lbl->setPixmap(px.scaled(displaySize, displaySize,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            lbl->setText(QString::fromStdString(choiceToString(c)));
    };
    setHand(ui->humanHandLabel,    p1Choice);
    setHand(ui->computerHandLabel, p2Choice);

    ui->humanScoreLabel->setText(QString::number(p1Score));
    ui->computerScoreLabel->setText(QString::number(p2Score));
    ui->tiesLabel->setText(QString::number(ties));

    // Determine round outcome from p1's perspective
    bool isTie  = (p1Choice == p2Choice);
    bool p1Wins = !isTie && (
        (p1Choice == Choice::ROCK     && p2Choice == Choice::SCISSORS) ||
        (p1Choice == Choice::SCISSORS && p2Choice == Choice::PAPER)    ||
        (p1Choice == Choice::PAPER    && p2Choice == Choice::ROCK));

    RoundResult fakeResult;
    fakeResult.humanChoice    = p1Choice;
    fakeResult.computerChoice = p2Choice;
    fakeResult.computerPrediction = p2Choice;
    fakeResult.predictionConfidence = 0;
    fakeResult.outcome = isTie ? RoundOutcome::TIE
                       : p1Wins ? RoundOutcome::HUMAN_WIN
                                : RoundOutcome::COMPUTER_WIN;

    addHistoryEntry(round, fakeResult);

    ui->winnerLabel->setText(isTie ? "Tie!" : (p1Wins ? "P1 Wins!" : "P2 Wins!"));
}

void MainWindow::onNetGameFinished(int p1Score, int p2Score, int ties) {
    QString msg = QString("Game over!\n\nP1: %1    P2: %2    Ties: %3")
                      .arg(p1Score).arg(p2Score).arg(ties);
    QMessageBox::information(this, "Network Game Over", msg);
    ui->netStatusLabel->setText("Game over. You can host a new game.");
    setNetworkControlsEnabled(true);
    // Reset engine first so its slots don't fire during NetworkManager teardown
    netEngine.reset();
    serverNm.reset();
    serverNm2.reset();
}

void MainWindow::onNetStatusMessage(const QString& msg) {
    ui->netStatusLabel->setText(msg);
}

// ── Client (join) side ───────────────────────────────────────────────────────

void MainWindow::onJoinClicked() {
    QString host = ui->joinIpEdit->text().trimmed();
    quint16 port = static_cast<quint16>(ui->joinPortSpinBox->value());
    QString name = ui->joinNameEdit->text().trimmed();
    if (name.isEmpty()) name = "Player";

    clientNm = std::make_unique<NetworkManager>(this);

    connect(clientNm.get(), &NetworkManager::connectedToServer,
            this, &MainWindow::onConnectedToServer);
    connect(clientNm.get(), &NetworkManager::disconnectedFromServer,
            this, &MainWindow::onDisconnectedFromServer);
    connect(clientNm.get(), &NetworkManager::connectionFailed,
            this, &MainWindow::onConnectionFailed);
    connect(clientNm.get(), &NetworkManager::gameStartReceived,
            this, &MainWindow::onGameStartReceived);
    connect(clientNm.get(), &NetworkManager::roundStartReceived,
            this, &MainWindow::onRoundStartReceived);
    connect(clientNm.get(), &NetworkManager::resultReceived,
            this, &MainWindow::onNetResultReceived);
    connect(clientNm.get(), &NetworkManager::gameOverReceived,
            this, &MainWindow::onNetGameOverReceived);

    clientNm->connectToServer(host, port, name);
    ui->netStatusLabel->setText(QString("Connecting to %1:%2 ...").arg(host).arg(port));
    setNetworkControlsEnabled(false);
    isNetworkClient = true;
}

void MainWindow::onDisconnectNetClicked() {
    if (clientNm) {
        clientNm->disconnectFromServer();
        clientNm.reset();
    }
    if (serverNm) {
        serverNm->stopServer();
        serverNm.reset();
    }
    serverNm2.reset();
    netEngine.reset();
    setNetworkControlsEnabled(true);
    setChoiceButtonsEnabled(false);
    ui->netStatusLabel->setText("Disconnected.");
    isNetworkClient = false;
}

void MainWindow::onConnectedToServer(const QString& serverName) {
    ui->netStatusLabel->setText(
        QString("Connected! Playing against: %1. Waiting for game to start...").arg(serverName));
    ui->computerNameLabel->setText(serverName);
    ui->humanNameLabel->setText(clientNm->playerName());
    resetDisplay();
    clearHistory();
}

void MainWindow::onDisconnectedFromServer() {
    ui->netStatusLabel->setText("Disconnected from server.");
    setNetworkControlsEnabled(true);
    setChoiceButtonsEnabled(false);
    clientNm.reset();
    isNetworkClient = false;
}

void MainWindow::onConnectionFailed(const QString& reason) {
    QMessageBox::warning(this, "Connection Failed",
        "Could not connect to server:\n" + reason);
    ui->netStatusLabel->setText("Connection failed: " + reason);
    setNetworkControlsEnabled(true);
    clientNm.reset();
    isNetworkClient = false;
}

void MainWindow::onGameStartReceived(int rounds, bool isSmart) {
    netTotalRounds  = rounds;
    netCurrentRound = 0;
    ui->netStatusLabel->setText(
        QString("Game starting! %1 rounds, %2 algorithm.")
            .arg(rounds).arg(isSmart ? "Smart" : "Random"));
    resetDisplay();
    clearHistory();
    ui->statusLabel->setText("Waiting for round to start...");
}

void MainWindow::onRoundStartReceived(int roundNum) {
    netCurrentRound = roundNum;
    ui->roundGroup->setTitle(QString("Round  %1 of %2").arg(roundNum).arg(netTotalRounds));
    ui->roundLabel->setText(QString("%1 / %2").arg(roundNum).arg(netTotalRounds));
    ui->statusLabel->setText("Your turn — pick Rock, Paper, or Scissors!");
    setChoiceButtonsEnabled(true);

    // Rock/Paper/Scissors buttons now send choices via network
    disconnect(ui->rockButton,     &QPushButton::clicked, nullptr, nullptr);
    disconnect(ui->paperButton,    &QPushButton::clicked, nullptr, nullptr);
    disconnect(ui->scissorsButton, &QPushButton::clicked, nullptr, nullptr);

    connect(ui->rockButton,     &QPushButton::clicked, this, [this]{ sendNetworkChoice(Choice::ROCK); });
    connect(ui->paperButton,    &QPushButton::clicked, this, [this]{ sendNetworkChoice(Choice::PAPER); });
    connect(ui->scissorsButton, &QPushButton::clicked, this, [this]{ sendNetworkChoice(Choice::SCISSORS); });
}

void MainWindow::sendNetworkChoice(Choice c) {
    if (!clientNm) return;
    setChoiceButtonsEnabled(false);
    clientNm->sendChoice(c);
    ui->statusLabel->setText("Waiting for result...");

    // Show my choice immediately
    const int displaySize = 130;
    QPixmap px = handPixmap(c);
    if (!px.isNull())
        ui->humanHandLabel->setPixmap(px.scaled(displaySize, displaySize,
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::onNetResultReceived(Choice myChoice, Choice oppChoice,
                                     int myScore, int oppScore, int ties) {
    const int displaySize = 130;
    auto setHand = [&](QLabel* lbl, Choice c) {
        QPixmap px = handPixmap(c);
        if (!px.isNull())
            lbl->setPixmap(px.scaled(displaySize, displaySize,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            lbl->setText(QString::fromStdString(choiceToString(c)));
    };
    setHand(ui->humanHandLabel,    myChoice);
    setHand(ui->computerHandLabel, oppChoice);

    ui->humanScoreLabel->setText(QString::number(myScore));
    ui->computerScoreLabel->setText(QString::number(oppScore));
    ui->tiesLabel->setText(QString::number(ties));

    bool isTie  = (myChoice == oppChoice);
    bool iWin   = !isTie && (
        (myChoice == Choice::ROCK     && oppChoice == Choice::SCISSORS) ||
        (myChoice == Choice::SCISSORS && oppChoice == Choice::PAPER)    ||
        (myChoice == Choice::PAPER    && oppChoice == Choice::ROCK));

    if (isTie) {
        ui->winnerLabel->setText("Tie!");
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#95d5b2;");
        ui->statusLabel->setText("It's a tie!");
    } else if (iWin) {
        ui->winnerLabel->setText("You Win!");
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#b7e4c7;");
        ui->statusLabel->setText("You won that round!");
    } else {
        ui->winnerLabel->setText("Opponent Wins!");
        ui->winnerLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#f4a261;");
        ui->statusLabel->setText("Opponent won that round.");
    }

    // Add to history
    addNetHistoryEntry(netCurrentRound, myChoice, oppChoice, iWin, isTie);
}

void MainWindow::onNetGameOverReceived(int myScore, int oppScore, int ties) {
    setChoiceButtonsEnabled(false);

    // Reconnect local game buttons
    disconnect(ui->rockButton,     &QPushButton::clicked, nullptr, nullptr);
    disconnect(ui->paperButton,    &QPushButton::clicked, nullptr, nullptr);
    disconnect(ui->scissorsButton, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->rockButton,     &QPushButton::clicked, this, &MainWindow::onRockClicked);
    connect(ui->paperButton,    &QPushButton::clicked, this, &MainWindow::onPaperClicked);
    connect(ui->scissorsButton, &QPushButton::clicked, this, &MainWindow::onScissorsClicked);

    QString winner;
    if (myScore > oppScore)       winner = "You win the game!";
    else if (oppScore > myScore)  winner = "Opponent wins the game.";
    else                           winner = "The game is a tie.";

    QMessageBox::information(this, "Network Game Over",
        winner + QString("\n\nYou: %1    Opponent: %2    Ties: %3")
            .arg(myScore).arg(oppScore).arg(ties));

    ui->netStatusLabel->setText("Game over. Connect again to play another.");
    setNetworkControlsEnabled(true);
    isNetworkClient = false;
    if (clientNm) {
        // Disconnect before reset to prevent onDisconnectedFromServer firing
        // during ~NetworkManager() and calling clientNm.reset() a second time.
        disconnect(clientNm.get(), &NetworkManager::disconnectedFromServer,
                   this, &MainWindow::onDisconnectedFromServer);
        clientNm.reset();
    }
}

void MainWindow::addNetHistoryEntry(int round, Choice myChoice, Choice oppChoice,
                                    bool iWon, bool isTie) {
    if (!historyLayout) return;

    const int thumbSize = 44;

    QFrame* card = new QFrame();
    card->setFrameShape(QFrame::StyledPanel);
    card->setStyleSheet(
        "QFrame { background-color: #2e4a3e; border-radius: 6px;"
        "         border: 1px solid #6aab82; }");

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(3);
    cardLayout->setContentsMargins(6, 4, 6, 4);

    QLabel* roundLbl = new QLabel(QString("Round %1").arg(round));
    roundLbl->setAlignment(Qt::AlignCenter);
    roundLbl->setStyleSheet("font-size: 11px; font-weight: bold; color: #a8d5b5; border: none;");
    cardLayout->addWidget(roundLbl);

    QHBoxLayout* handsRow = new QHBoxLayout();
    handsRow->setSpacing(4);

    auto makeThumb = [&](Choice c) {
        QLabel* lbl = new QLabel();
        lbl->setFixedSize(thumbSize, thumbSize);
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("background-color: #ffffff; border-radius: 6px; border: 1px solid #a8d5b5;");
        QPixmap px = handPixmap(c);
        if (!px.isNull())
            lbl->setPixmap(px.scaled(thumbSize - 4, thumbSize - 4,
                                     Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            lbl->setText(QString::fromStdString(choiceToString(c)));
        return lbl;
    };

    handsRow->addWidget(makeThumb(myChoice));
    QLabel* vsLbl = new QLabel("vs");
    vsLbl->setAlignment(Qt::AlignCenter);
    vsLbl->setStyleSheet("font-size: 10px; color: #a8d5b5; border: none;");
    handsRow->addWidget(vsLbl);
    handsRow->addWidget(makeThumb(oppChoice));
    cardLayout->addLayout(handsRow);

    QLabel* resultLbl = new QLabel(isTie ? "Tie!" : (iWon ? "You Win!" : "Opp Wins!"));
    resultLbl->setAlignment(Qt::AlignCenter);
    resultLbl->setStyleSheet("font-size: 11px; font-weight: bold; border: none; color: "
        + (isTie ? QString("#fff176;") : iWon ? QString("#81c784;") : QString("#e57373;")));
    cardLayout->addWidget(resultLbl);

    historyLayout->insertWidget(historyLayout->count() - 1, card);
    ui->historyScrollArea->verticalScrollBar()->setValue(
        ui->historyScrollArea->verticalScrollBar()->maximum());
}

