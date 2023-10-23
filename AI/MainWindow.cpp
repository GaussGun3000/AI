#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    connect(&myThread, &DirectionalSearch::updateStats, this, &MainWindow::updateStats);
    mutex.lock();
    QVector<int> startState = {6, 0, 8, 5, 2, 1, 4, 3, 7};
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    ds.reset(new DirectionalSearch(&mutex, 15, startState, targetState));
    //connect
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
