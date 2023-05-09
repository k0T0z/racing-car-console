#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "speed_meter/speedmeter.h"
#include "rpm_meter/rpmmeter.h"
#include <iostream>
#include <QMainWindow>
#include <QPainter>
#include <cmath>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SpeedMeter *speed_meter;
    RPMMeter *rpm_meter;

    QWidget *main_widget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
