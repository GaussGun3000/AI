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
    QScopedPointer<DirectionalSearch> ds;
    QMutex mutex;

public slots:
    void stepButtonClicked();
    void completeButtonClicked();
    void startButtonClicked();
    void updateStatLabels(uint32_t depth);

signals:
    void updateStatsFromThread(uint32_t depth);
};
