#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Choice.h"
#include "ComputerPlayer.h"
#include "GUIGameEngine.h"
#include "GUIHumanPlayer.h"
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
    void onStartClicked();
    void onResetLearningClicked();
    void onViewDataClicked();
    void onRockClicked();
    void onPaperClicked();
    void onScissorsClicked();

    void onRoundResultReady(int round, int totalRounds, RoundResult result,
                            int humanScore, int computerScore, int ties);
    void onGameFinished(int humanScore, int computerScore, int ties);

private:
    Ui::MainWindow* ui;

    std::unique_ptr<GUIHumanPlayer>  humanPlayer;
    std::unique_ptr<ComputerPlayer>  computerPlayer;
    std::unique_ptr<GUIGameEngine>   gameEngine;

    // Hand images cropped from hands.jpg (order: Paper, Scissors, Rock)
    QPixmap paperPixmap;
    QPixmap scissorsPixmap;
    QPixmap rockPixmap;

    void loadHandImages();
    QPixmap handPixmap(Choice c) const;
    void setChoiceButtonsEnabled(bool enabled);
    void resetDisplay();
    void clearHistory();
    void addHistoryEntry(int round, RoundResult result);
    QString outcomeString(RoundOutcome outcome) const;

    QVBoxLayout* historyLayout = nullptr;
};

#endif
