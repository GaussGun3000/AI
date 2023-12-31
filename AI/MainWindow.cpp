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
    ash1 = new AStar(&mutex, GreedySearch::HFunction::h1, startState, targetState);
    ash2 = new AStar(&mutex, GreedySearch::HFunction::h2, startState, targetState);

    connect(gsh1, &GreedySearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(gsh1, &GreedySearch::finished, this, &MainWindow::updateFinishedStatLabels);
    connect(gsh2, &GreedySearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(gsh2, &GreedySearch::finished, this, &MainWindow::updateFinishedStatLabels);
    connect(ash1, &GreedySearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(ash1, &GreedySearch::finished, this, &MainWindow::updateFinishedStatLabels);
    connect(ash2, &GreedySearch::updateStats, this, &MainWindow::updateStatLabels);
    connect(ash2, &GreedySearch::finished, this, &MainWindow::updateFinishedStatLabels);

    ui.setupUi(this);
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
}

MainWindow::~MainWindow()
{}

void MainWindow::stepButtonClicked()
{   
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� � ��������"));
    mutex.unlock();
    mutex.lock();
    //maybe something else
}

void MainWindow::completeButtonClicked()
{
    this->inSingleStepMode = false;
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� � ��������"));
    ui.stepButton->setDisabled(true);
    ui.completeButton->setDisabled(true);
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
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah1)
    {
        ash1->start();
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah2)
    {
        ash2->start();
    }
   
    update();
}

void MainWindow::updateStatLabels(quint32 depth)
{
    ui.depthLabel->setText(QString::number(depth));
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::Greedyh1)
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
                ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
            }
        }
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Greedyh2)
    {
        ui.timeComplexityLabel->setText(QString::number(gsh2->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(gsh2->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.lastStateLabel->setText(QString(gsh2->getLastNodeStateString()));
            if (gsh2->getStepCount() > 1)
            {
                ui.parentStateLabel->setText(QString(gsh2->getParentLastNodeStateString()));
            }
            else
            {
                ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
            }
        }
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah1)
    {
        ui.timeComplexityLabel->setText(QString::number(ash1->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(ash1->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.lastStateLabel->setText(QString(ash1->getLastNodeStateString()));
            if (ash1->getStepCount() > 1)
            {
                ui.parentStateLabel->setText(QString(ash1->getParentLastNodeStateString()));
            }
            else
            {
                ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
            }
        }
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah2)
    {
        ui.timeComplexityLabel->setText(QString::number(ash2->getStepCount()));
        ui.capacitiveComplexityLabel->setText(QString::number(ash2->getNodeCount()));
        if (this->inSingleStepMode)
        {
            ui.lastStateLabel->setText(QString(ash2->getLastNodeStateString()));
            if (ash2->getStepCount() > 1)
            {
                ui.parentStateLabel->setText(QString(ash2->getParentLastNodeStateString()));
            }
            else
            {
                ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
            }
        }
    }
}

void MainWindow::updateFinishedStatLabels()
{
    auto mode = ui.typeComboBox->currentIndex();
    if (static_cast<SearchMode>(mode) == SearchMode::Greedyh1)
    {
        uint32_t resDepth = gsh1->getResultingDepth();
        if (resDepth == -1)
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �� �������"));
        else
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �������"));
        ui.depthLabel->setText(QString::number(gsh1->getResultingDepth()));
        ui.lastStateLabel->setText(QString(gsh1->getLastNodeStateString()));
        if (gsh1->getStepCount() > 1)
        {
            ui.parentStateLabel->setText(QString(gsh1->getParentLastNodeStateString()));
        }
        else
        {
            ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
        }
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Greedyh2)
    {
        uint32_t resDepth = gsh2->getResultingDepth();
        if (resDepth == -1)
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �� �������"));
        else
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �������"));
        ui.depthLabel->setText(QString::number(gsh2->getResultingDepth()));
        ui.lastStateLabel->setText(QString(gsh2->getLastNodeStateString()));
        if (gsh2->getStepCount() > 1)
        {
            ui.parentStateLabel->setText(QString(gsh2->getParentLastNodeStateString()));
        }
        else
        {
            ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
        }  
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah1)
    {
        uint32_t resDepth = ash1->getResultingDepth();
        if (resDepth == -1)
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �� �������"));
        else
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �������"));
        ui.depthLabel->setText(QString::number(ash1->getResultingDepth()));
        ui.lastStateLabel->setText(QString(ash1->getLastNodeStateString()));
        if (ash1->getStepCount() > 1)
        {
            ui.parentStateLabel->setText(QString(ash1->getParentLastNodeStateString()));
        }
        else
        {
            ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
        }
    }
    else if (static_cast<SearchMode>(mode) == SearchMode::Ah2)
    {
        uint32_t resDepth = ash2->getResultingDepth();
        if (resDepth == -1)
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �� �������"));
        else
            ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� ��������. ������� �������"));
        ui.depthLabel->setText(QString::number(ash2->getResultingDepth()));
        ui.lastStateLabel->setText(QString(ash2->getLastNodeStateString()));
        if (ash2->getStepCount() > 1)
        {
            ui.parentStateLabel->setText(QString(ash2->getParentLastNodeStateString()));
        }
        else
        {
            ui.parentStateLabel->setText(QString::fromLocal8Bit("��� ��������� ����"));
        }
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
    ui.depthLabel->setText("0");
    ui.parentStateLabel->clear();
    ui.lastStateLabel->clear();
    ui.timeComplexityLabel->setText("0");
    ui.capacitiveComplexityLabel->setText("0");
    ui.searchStatusLabel->setText(QString::fromLocal8Bit("����� �� �����"));
}
