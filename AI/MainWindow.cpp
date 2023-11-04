#include "MainWindow.h"
#include "Node.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mutex.lock();
    QVector<int> startState = { 6, 0, 8, 5, 2, 1, 4, 3, 7 };
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    //QVector<int> targetState = { 6, 2, 8, 5, 3, 1, 4, 0, 7 };
    int maxDepth = 500000;
    bds = new BiDirectionalSearch(&mutex, maxDepth, startState, targetState);
    dfs = new DFS(&mutex, maxDepth, startState, targetState);
    connect(bds, &BiDirectionalSearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(dfs, &DFS::updateStats, this, &MainWindow::updateStatLabels);
    connect(bds, &BiDirectionalSearch::finished, this, &MainWindow::updateFinishedStatLabelsBDS);
    connect(dfs, &DFS::finished, this, &MainWindow::updateFinishedStatLabelsDFS);
    
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateNodeNumLabel);
    timer->start(1);

    ui.setupUi(this);
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
}

MainWindow::~MainWindow()
{}

void MainWindow::stepButtonClicked()
{   
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск в процессе"));
    mutex.unlock();
    mutex.lock();
    //maybe something else
}

void MainWindow::completeButtonClicked()
{
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск в процессе"));
    ui.stepButton->setDisabled(true);
    mutex.unlock();
}

void MainWindow::startButtonClicked()
{
    ui.startButton->setDisabled(true);
    ui.stepButton->setDisabled(false);
    ui.completeButton->setDisabled(false);
    ui.typeComboBox->setDisabled(true);
    auto mode = ui.typeComboBox->currentIndex();
    if (mode == 0)
    {
        bds->start();
    }
    else
    {
        dfs->start();
    }
   
    update();
}

void MainWindow::updateStatLabels(quint32 depth)
{
    ui.depthLabel->setText(QString::number(depth));
    update();
}

void MainWindow::updateFinishedStatLabelsBDS()
{
    uint32_t resDepth = bds->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение не найдено"));
    else
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение найдено"));
    ui.depthLabel->setText(QString::number(bds->getResultingDepth()));
    update();
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
    ui.startButton->setDisabled(false);
    ui.typeComboBox->setDisabled(false);
    mutex.lock();
}

void MainWindow::updateFinishedStatLabelsDFS()
{
    uint32_t resDepth = dfs->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение не найдено"));
    else
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение найдено"));
    ui.depthLabel->setText(QString::number(dfs->getResultingDepth()));
    update();
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
    ui.startButton->setDisabled(false);
    ui.typeComboBox->setDisabled(false);
    mutex.lock();
}

void MainWindow::updateNodeNumLabel()
{
    auto mode = ui.typeComboBox->currentIndex();
    if (mode == 0)
    {
        if (bds->getNodesNumSize() != 0)
            ui.nodesNumLabel->setText(QString::number(bds->getNodesNumSize()));
    }
    else
    {
        if (dfs->getNodesNumSize() != 0)
            ui.nodesNumLabel->setText(QString::number(dfs->getNodesNumSize()));
    }
}
