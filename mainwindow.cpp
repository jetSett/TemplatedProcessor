#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const unsigned screen_offset = 0xb000;

const unsigned screen_width = 160;
const unsigned screen_height = 128;
const unsigned screen_scale = 3;

const unsigned zero_frames = 8;
const unsigned instructionsPerFrame = 100;

MainWindow::MainWindow(QWidget *parent) : ui(new Ui::MainWindow),
    QMainWindow(parent), _screen(screen_width*screen_scale, screen_height*screen_scale, QImage::Format_RGB444)
{
    ui->setupUi(this);

    _timer = new QTimer(this);

    ui->screenView->setMinimumHeight(screen_height*screen_scale+3);
    ui->screenView->setMinimumWidth(screen_width*screen_scale+3); // +3 for a more beautiful screen ;)
    ui->screenView->setMaximumHeight(screen_height*screen_scale+3);
    ui->screenView->setMaximumWidth(screen_width*screen_scale+3);

    ui->warnigLabel->setText(QString("Warning, 1*1 pixel in memory = ")+QString::number(screen_scale)+ QString("*") + QString::number(screen_scale) + QString("pixels on screen"));

    _scene = new QGraphicsScene(this);

    ui->screenView->setScene(_scene);

    connect(&_proc, SIGNAL(fileLoaded()), this, SLOT(fileLoaded()));
    connect(&_proc, SIGNAL(stepEnd()), this, SLOT(updateReg()));
    connect(&_proc, SIGNAL(stepEnd()), this, SLOT(log()));
    connect(&_proc, SIGNAL(stepEnd()), this, SLOT(logMem()));
    connect(&_proc, SIGNAL(stepEnd()), this, SLOT(updateScreenRun()));
    connect(ui->updateScreenButton, SIGNAL(pressed()), this, SLOT(updateScreen()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

    updateReg();
    logMem();
    updateScreen();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileLoaded(){
    QMessageBox::information(this, "Information", "File has been properly loaded");
    log();
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
    if(_proc.loaded()){
        if(_proc.ended()){
            QMessageBox::information(this, "Ended", "You have reached the end of the program");
        }else{
             _proc.step();
             updateReg();
             updateScreen();
             log();
             logMem();
        }
    }else{
        QMessageBox::critical(this, "Error", "Nothing was loaded");
    }
}

void MainWindow::on_goButton_pressed(){
    ui->goButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    _timer->start(1);
}

void MainWindow::on_stopButton_pressed(){
    ui->goButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    _timer->stop();
}

void MainWindow::logMem(){
    if(ui->memGroupBox->isChecked()){
        QString t;
        for(unsigned i = 0; i<100; ++i){
            t += QString::number(screen_offset+i,16) + QString(" : ") + QString::number(_proc.getMemory()[screen_offset+i], 16) + QString("\n");
        }
        ui->memTextEdit->setText(t);
    }
}

void MainWindow::updateScreenRun(){
    static int counter = 0;
    if(ui->updateScreenGroupBox->isChecked()){
        counter ++;
        if(counter == ui->updateScreenSpinBox->value()){
            updateScreen();
            counter = 0;
        }
    }


}

void MainWindow::updateScreen(){

    for(unsigned x = 0; x < screen_width; ++x){
        for(unsigned y = 0; y < screen_height; ++y){
            for(unsigned x1 = 0; x1 < screen_scale; ++x1){
                for(unsigned y1 = 0; y1 < screen_scale; ++y1){
                    word pix = _proc.getMemory()[screen_offset+x+y*screen_width];
                    unsigned r = 16 * ( (pix & 0x0F00)>>8 );
                    unsigned g = 16 * ( (pix & 0x00F0)>>4 );
                    unsigned b = 16 * ( (pix & 0x000F)>>0 );
                    _screen.setPixelColor(QPoint(screen_scale*x+x1, screen_scale*y + y1), QColor(r, g, b));
                }
            }
        }
    }

    _scene->clear();
    QPixmap pm = QPixmap::fromImage(_screen);
    _scene->addPixmap(pm);
    _scene->update();
}

void MainWindow::log(){
    if(ui->historygroupBox->isChecked()){
        ui->historyTextEdit->setText(QString(_proc.printState().c_str()) + ui->historyTextEdit->toPlainText());
    }
}

void MainWindow::step(){
    static int counter = 0;
    for(int a = 0; a<ui->stepsByFramesSpinBox->value(); ++a){
        if(not _proc.ended()){
            _proc.step();
        }else{
            on_stopButton_pressed();
            return;
        }
    }

    updateReg();
    log();
    counter ++;
    if(counter == zero_frames)
        counter = 0;
}
