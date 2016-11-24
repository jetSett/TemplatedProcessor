#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include "processor.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void fileLoaded();
    void updateReg();
    void updateScreen();
    void log();
    void logMem();

    void updateScreenRun();
    void updateMemRun();

    void step();

    void on_openAction_triggered();
    void on_stepButton_pressed();
    void on_goButton_pressed();
    void on_stopButton_pressed();
    void on_resetButton_pressed();

    void minMem(int);

private:
    Ui::MainWindow *ui;

    Processor _proc;

    QTimer* _timer;

    QImage _screen;
    QPainter* _painter;
    QGraphicsScene* _scene;
};

#endif // MAINWINDOW_HPP
