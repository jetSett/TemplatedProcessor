#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
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
    void on_openAction_triggered();
    void on_stepButton_pressed();

private:
    Ui::MainWindow *ui;
    Processor _proc;
};

#endif // MAINWINDOW_HPP
