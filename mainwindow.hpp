#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFileDialog>
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
    void on_openAction_triggered();
    void on_stepButton_pressed();
    void on_goButton_pressed();
    void logMem();

signals:
    void nextGo();

private:
    bool _go;

    QTimer* _timer;

    Ui::MainWindow *ui;
    Processor _proc;



    QImage _screen;
    QPainter* _painter;
    QGraphicsScene* _scene;
};

#endif // MAINWINDOW_HPP
