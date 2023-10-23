#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mutex.lock();
    //ds.reset(new DirectionalSearch());
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
