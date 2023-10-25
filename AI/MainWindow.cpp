#include "MainWindow.h"
#include "Node.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Node::Action action = Node::Action::MoveDown;
    auto action2 = action;
    mutex.lock();
    QVector<int> startState = { 6, 0, 8, 5, 2, 1, 4, 3, 7 };
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    //QVector<int> targetState = { 6, 2, 8, 5, 3, 1, 4, 0, 7 };
    int maxDepth = 15;
    ds = new DirectionalSearch(&mutex, maxDepth, startState, targetState);
    connect(ds, &DirectionalSearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(ds, &DirectionalSearch::finished, this, &MainWindow::updateFinishedStatLabels);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateNodeNumLabel);
    timer->start(100);
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
    ds->start();
    update();
}

void MainWindow::updateStatLabels(quint32 depth)
{
    ui.depthLabel->setText(QString::number(depth));
    update();
}

void MainWindow::updateFinishedStatLabels()
{
    uint32_t resDepth = ds->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение не найдено"));
    else
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение найдено"));
    ui.depthLabel->setText(QString::number(ds->getResultingDepth()));
    update();
}

void MainWindow::updateNodeNumLabel()
{
    if(ds->getNodesNumSize() != 0)
        ui.nodesNumLabel->setText(QString::number(ds->getNodesNumSize()));
}
