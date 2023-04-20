#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    speedMeter = new SpeedMeter(this);
    setCentralWidget(speedMeter);
}

MainWindow::~MainWindow() {
    delete speedMeter;
};







































