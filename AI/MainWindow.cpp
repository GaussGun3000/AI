#include "MainWindow.h"
#include "Node.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Node::Action action = Node::Action::MoveDown;
    auto action2 = action;
    mutex.lock();
    QVector<int> startState = { 6, 0, 8, 5, 2, 1, 4, 3, 7 };
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    int maxDepth = 15;
    ds = new DirectionalSearch(&mutex, maxDepth, startState, targetState);
    connect(ds, &DirectionalSearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(ds, &DirectionalSearch::finished, this, &MainWindow::updateFinishedStatLabels);
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
    ui.searchStatusLabel->setText("Поиск в процессе");
    ds->start();
    update();
}

void MainWindow::updateStatLabels(uint32_t depth)
{
    ui.depthLabel->setText(QString::number(depth));
    update();
}

void MainWindow::updateFinishedStatLabels()
{
    uint32_t resDepth = ds->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText("Поиск завершен. Решение не найдено");
    else
        ui.searchStatusLabel->setText("Поиск завершен. Решение найдено");
    update();
}
