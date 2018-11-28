#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void blocked();

private slots:
    void on_blocked();
    void on_moveButton_clicked();
    void on_verticalButton_pressed();
    void on_horizontalButton_pressed();
    void on_upRadioButton_toggled(bool checked);
    void on_downRadioButton_toggled(bool checked);
    void on_leftRadioButton_toggled(bool checked);
    void on_rightRadioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;          // a surface for
    QGraphicsEllipseItem* circle;   // drawing a circle

    QTimer timer_;          // for continuous moving

    const int STEP = 20;    // how much to move at a time

    bool is_horizontal_;    // is_right
    bool is_vertical_;      // is_down

    void circle_move();     // moves the circle to a desired direction
};

#endif // MAINWINDOW_HH
