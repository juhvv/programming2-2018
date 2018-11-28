#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), is_horizontal_(false), is_vertical_(false)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw a circle
    scene = new QGraphicsScene(this);

    ui->graphicsView->setGeometry(10, 270, 682, 262);   // x, y, height, width
    ui->graphicsView->setScene(scene);

    // Height and width of the scene are decreased by 3 from those of
    // the graphicsView
    // In addition 682-2 and 262-2 are divisible by by STEP (20)
    // and by the size (20) of the circle below
    scene->setSceneRect(0, 0, 682-3, 262-3);

    // Defining the color and outline of the circle
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    circle = scene->addEllipse(0, 0, 20, 20, blackPen, redBrush);

    // Initial values for radio buttons and push buttons
    ui->upRadioButton->setChecked(true);
    ui->leftRadioButton->setChecked(true);

    ui->verticalButton->setText("Set down");
    ui->horizontalButton->setText("Set right");

    // A non-singleshot timer fires every interval (1000) milliseconds,
    // which makes circle_move function to be called,
    // until the timer is stopped
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::circle_move);

    // Clearing the status label makes the text given in ui file to disappear
    ui->statusLabel->clear();

    // It is very stupid to connect an object to itself
    connect(this, &MainWindow::blocked, this, &MainWindow::on_blocked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::circle_move()
{
    // Making the earlier text to disappear
    ui->statusLabel->clear();

    // Current position of the circle
    qreal xx = circle->x();
    qreal yy = circle->y();

    qDebug() << xx << " and " << yy;

    // Calculating the displacement that can be either
    // positive or negative, depending on the direction
    qreal deltaX, deltaY;
    if(is_horizontal_) {
        deltaX = static_cast<qreal>(STEP);  // right (positive step)
    } else {
        deltaX = static_cast<qreal>(-STEP); // left (negative step)
    }
    if(is_vertical_) {
        deltaY = static_cast<qreal>(STEP);  // down (positive step)
    } else {
        deltaY = static_cast<qreal>(-STEP); // up (negative step)
    }

    // New position of the circle
    xx += deltaX;
    yy += deltaY;

    // If the new position is in the scene, the circle can be moved there
    // otherwise moving stops
    QRectF rect = scene->sceneRect();
    if(rect.contains(xx, yy)) {
        circle->moveBy(deltaX, deltaY);
        ui->statusLabel->setText("Moving");
    } else {
        timer_.stop();
        ui->moveButton->setDisabled(true);
        emit blocked();     // This could be replaced with a normal function call,
    }                       // but the purpose is to show how to use emit
}

void MainWindow::on_blocked()
{
    ui->statusLabel->setText("Blocked");
}

void MainWindow::on_moveButton_clicked()
{
    ui->moveButton->setDisabled(true);
    timer_.start(1000);
}

// The rest of the functions handle push button presses
// and radio button togglings and keep them consistent
void MainWindow::on_verticalButton_pressed()
{
    is_vertical_ = !is_vertical_; // change vertical
    if(is_vertical_) {
        ui->verticalButton->setText("Set up");
        ui->downRadioButton->setChecked(true);
    } else {
        ui->verticalButton->setText("Set down");
        ui->upRadioButton->setChecked(true);
    }
    ui->moveButton->setDisabled(false);
}

void MainWindow::on_horizontalButton_pressed()
{
    is_horizontal_ = !is_horizontal_; // change horizontal
    if(is_horizontal_) {
        ui->horizontalButton->setText("Set left");
        ui->rightRadioButton->setChecked(true);
    } else {
        ui->horizontalButton->setText("Set right");
        ui->leftRadioButton->setChecked(true);
    }
    ui->moveButton->setDisabled(false);
}

void MainWindow::on_upRadioButton_toggled(bool checked)
{
    ui->upRadioButton->setChecked(checked);
    is_vertical_ = false;
    ui->verticalButton->setText("Set down");
    ui->moveButton->setEnabled(true);
}

void MainWindow::on_downRadioButton_toggled(bool checked)
{
    ui->downRadioButton->setChecked(checked);
    is_vertical_ = true;
    ui->verticalButton->setText("Set up");
    ui->moveButton->setEnabled(true);
}

void MainWindow::on_leftRadioButton_toggled(bool checked)
{
    ui->leftRadioButton->setChecked(checked);
    is_horizontal_ = false;
    ui->horizontalButton->setText("Set right");
    ui->moveButton->setEnabled(true);
}

void MainWindow::on_rightRadioButton_toggled(bool checked)
{
    ui->rightRadioButton->setChecked(checked);
    is_horizontal_ = true;
    ui->horizontalButton->setText("Set left");
    ui->moveButton->setEnabled(true);
}
