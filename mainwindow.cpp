#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *main_layout = new QHBoxLayout;

    speed_meter = new SpeedMeter(this);

    main_layout->addWidget(speed_meter);
    main_layout->setStretchFactor(speed_meter, 1);

    main_widget = new QWidget;
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);

    delete main_layout;
}

MainWindow::~MainWindow() {
    delete speed_meter;
    delete main_widget;
};







































