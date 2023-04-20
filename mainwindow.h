#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "speed_meter/speedmeter.h"
#include <iostream>
#include <QMainWindow>
#include <QPainter>
#include <cmath>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SpeedMeter *speedMeter;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
