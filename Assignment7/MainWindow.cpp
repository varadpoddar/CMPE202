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
