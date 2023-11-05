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
    this->inSingleStepMode = false;
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск в процессе"));
    ui.stepButton->setDisabled(true);
    mutex.unlock();
}

void MainWindow::startButtonClicked()
{
    this->inSingleStepMode = true;
    ui.startButton->setDisabled(true);
    ui.stepButton->setDisabled(false);
    ui.completeButton->setDisabled(false);
    ui.typeComboBox->setDisabled(true);
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::BiDS)
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
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::BiDS)
    {
        ui.timeComplexityLabel->setText(QString::number(bds->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(bds->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.startDirStateLabel->setText(QString(bds->getLastStartNodeStateString()));
            ui.targetDirStateLabel->setText(QString(bds->getLastTargetNodeStateString()));
        }
    }
    else
    {
        ui.timeComplexityLabel->setText(QString::number(dfs->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(dfs->getNodeCount()));
        if (this->inSingleStepMode) 
            ui.startDirStateLabel->setText(QString(dfs->getLastNodeStateString()));
    }
}

void MainWindow::updateFinishedStatLabelsBDS()
{
    uint32_t resDepth = bds->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение не найдено"));
    else
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение найдено"));
    ui.depthLabel->setText(QString::number(bds->getResultingDepth()));
    ui.startDirStateLabel->setText(QString(bds->getLastStartNodeStateString()));
    ui.targetDirStateLabel->setText(QString(bds->getLastTargetNodeStateString()));
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
    ui.startDirStateLabel->setText(QString(dfs->getLastNodeStateString()));
    update();
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
    ui.startButton->setDisabled(false);
    ui.typeComboBox->setDisabled(false);
    mutex.lock();
}

void MainWindow::modeChanged()
{
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::BiDS)
    {
        ui.biDirectWidget->setVisible(true);
        ui.targetDirLabel->setVisible(true);
        ui.startDirLabel->setVisible(true);

    }
    else
    {
        ui.biDirectWidget->setVisible(false);
        ui.targetDirLabel->setVisible(false);
        ui.startDirLabel->setVisible(false);
    }
}
