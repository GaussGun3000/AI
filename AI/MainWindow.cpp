#include "MainWindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("* { font-size: 15px; }");
    mutex.lock();
    QVector<int> startState = { 6, 0, 8, 5, 2, 1, 4, 3, 7 };
    QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
    //QVector<int> targetState = { 6, 2, 8, 5, 3, 1, 4, 0, 7 };
    int maxDepth = 500000;
    gsh1 = new GreedySearch(&mutex, GreedySearch::HFunction::h1, startState, targetState);
    gsh2 = new GreedySearch(&mutex, GreedySearch::HFunction::h2, startState, targetState);
   // astar = new
    connect(gsh1, &GreedySearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(gsh1, &GreedySearch::finished, this, &MainWindow::updateFinishedStatLabels);

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
    if (static_cast<SearchMode>(mode) == SearchMode::Greedyh1)
    {
        gsh1->start();
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Greedyh2)
    {
        gsh2->start();
    }
   
    update();
}

void MainWindow::updateStatLabels(quint32 depth)
{
    ui.depthLabel->setText(QString::number(depth));
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::Greedyh1 || static_cast<SearchMode>(mode) == SearchMode::Greedyh2)
    {
        ui.timeComplexityLabel->setText(QString::number(gsh1->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(gsh1->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.lastStateLabel->setText(QString(gsh1->getLastNodeStateString()));
            if (gsh1->getStepCount() > 1)
            {
                ui.parentStateLabel->setText(QString(gsh1->getParentLastNodeStateString()));
            } 
            else
            {
                ui.parentStateLabel->setText(QString::fromLocal8Bit("Это начальный узел"));
            }
        }
    }
    /*
    else
    {
        ui.timeComplexityLabel->setText(QString::number(dfs->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(dfs->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.startDirStateLabel->setText(QString(dfs->getLastNodeStateString()));
            if(dfs->getStepCount() > 1)
                ui.parentStartDirStateLabel->setText(QString(dfs->getParentLastNodeStateString()));
            else
                ui.parentStartDirStateLabel->setText(QString::fromLocal8Bit("Это начальный узел"));
        }
            
    }
    */
}

void MainWindow::updateFinishedStatLabels()
{
    uint32_t resDepth = gsh1->getResultingDepth();
    if (resDepth == -1)
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение не найдено"));
    else
        ui.searchStatusLabel->setText(QString::fromLocal8Bit("Поиск завершен. Решение найдено"));
    ui.depthLabel->setText(QString::number(gsh1->getResultingDepth()));
    ui.lastStateLabel->setText(QString(gsh1->getLastNodeStateString()));
    if (gsh1->getStepCount() > 1)
    {
        ui.parentStateLabel->setText(QString(gsh1->getParentLastNodeStateString()));
    }
    else
    {
        ui.parentStateLabel->setText(QString::fromLocal8Bit("Это начальный узел"));
    }
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
    ui.parentStateLabel->clear();
    ui.lastStateLabel->clear();
    
}
