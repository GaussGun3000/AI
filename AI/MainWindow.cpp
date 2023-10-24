#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mutex.lock();
    QVector<int> startState = { 6, 0, 8, 5, 2, 1, 4, 3, 7 };
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    int maxDepth = 15;
    ds = new DirectionalSearch(&mutex, maxDepth, startState, targetState);
    connect(ds, &DirectionalSearch::updateStats, this, &MainWindow::updateStats);
    connect(ds, &DirectionalSearch::finished, this, &MainWindow::updateStats);
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::stepButtonClicked()
{   
    mutex.unlock();
    mutex.lock();
    //maybe something else
}

void MainWindow::completeButtonClicked()
{
    mutex.unlock();
}

void MainWindow::startButtonClicked()
{
    
}

void MainWindow::updateStats(uint32_t depth)
{
    ui.depthLabel->setText(QString::number(depth));
}
