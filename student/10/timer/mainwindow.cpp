#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::tickSecs);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::timerStartStop);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetCounters);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::timerStartStop);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);

    resetCounters();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerStartStop()
{
    if (timer->isActive()) {
        timer->stop();

    } else {
        timer->start(1000);
    }
}


void MainWindow::tickMins()
{
    double curMins = ui->lcdNumberMin->value();
    ui->lcdNumberMin->display(curMins + 1);
}

void MainWindow::tickSecs()
{
    double curSecs = ui->lcdNumberSec->value();
    if (curSecs + 1 == 60) {
        ui->lcdNumberSec->display(0);
        tickMins();

    } else {
        ui->lcdNumberSec->display(curSecs + 1);
    }
}

void MainWindow::resetCounters()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}
