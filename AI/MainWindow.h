#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "BidirectionalDFS.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    BiDirectionalSearch* bds;
    DFS* dfs;
    QMutex mutex;
    bool inSingleStepMode;
    enum class SearchMode {Greedyh1=0, Greedyh2=1, Ah1=2, Ah2=3};

public slots:
    void stepButtonClicked();
    void completeButtonClicked();
    void startButtonClicked();
    void updateStatLabels(quint32 depth);
    void updateFinishedStatLabelsBDS();
    void updateFinishedStatLabelsDFS();
    void modeChanged();

signals:
    void updateStatsFromThread(uint32_t depth);
};
