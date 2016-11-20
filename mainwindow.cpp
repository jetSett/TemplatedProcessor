#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateReg();

    connect(&_proc, SIGNAL(fileLoaded()), this, SLOT(fileLoaded()));
    connect(&_proc, SIGNAL(stepEnd()), this, SLOT(updateReg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileLoaded(){
    QMessageBox::information(this, "Information", "File has been properly loaded");
}

void MainWindow::updateReg(){
    QString text;
    text += "pc : ";
    text += QString::number(_proc.getPc());
    text += "\n";
    unsigned i = 0;
    for(auto r : _proc.getRegbox()){
        text += "r"; text += QString::number(i); text += " : "; text += QString::number(r, 16); text += "\n";
        i++;
    }
    ui->regText->setText(text);
}

void MainWindow::on_openAction_triggered(){
    QString file = QFileDialog::getOpenFileName(this, "Open", "Please choose your obj file");
    _proc.loadFile(file.toStdString());
}

void MainWindow::on_stepButton_pressed(){
    _proc.step();
}
