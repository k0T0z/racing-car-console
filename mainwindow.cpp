#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *main_layout = new QHBoxLayout;

    speed_meter = new SpeedMeter(this);
    rpm_meter = new RPMMeter(this);

    main_layout->addWidget(speed_meter);
    main_layout->addWidget(rpm_meter);
    //main_layout->setStretchFactor(speed_meter, 1);

    main_widget = new QWidget;
    //main_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_widget->setLayout(main_layout);
    setCentralWidget(speed_meter);

    delete main_layout;
}

MainWindow::~MainWindow() {
    delete speed_meter;
    delete rpm_meter;
    delete main_widget;
};







































