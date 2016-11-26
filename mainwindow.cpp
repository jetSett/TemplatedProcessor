#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const unsigned screen_offset = 0xb000;

const unsigned screen_width = 160;
const unsigned screen_height = 128;
const unsigned screen_scale = 3;

const unsigned zero_frames = 8;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), _screen(screen_width*screen_scale, screen_height*screen_scale, QImage::Format_RGB444), _workThread(new QThread(this))
{
    ui->setupUi(this);

    _worker = new Worker(&_proc, 5000);
    _worker->moveToThread(_workThread);

    connect(_workThread, SIGNAL(started()), _worker, SLOT(start()));

//    _timer = new QTimer(this);

    ui->screenView->setMinimumHeight(screen_height*screen_scale+3);
    ui->screenView->setMinimumWidth(screen_width*screen_scale+3); // +3 for a more beautiful screen ;)
    ui->screenView->setMaximumHeight(screen_height*screen_scale+3);
    ui->screenView->setMaximumWidth(screen_width*screen_scale+3);

    ui->warnigLabel->setText(QString("Warning, 1*1 pixel in memory = ")+QString::number(screen_scale)+ QString("*") + QString::number(screen_scale) + QString("pixels on screen"));

    _scene = new QGraphicsScene(this);

    ui->screenView->setScene(_scene);

    connect(&_proc, SIGNAL(fileLoaded()), this, SLOT(fileLoaded()));
    connect(_worker, SIGNAL(log()), this, SLOT(updateReg()));
    connect(_worker, SIGNAL(log()), this, SLOT(log()));

    connect(_worker, SIGNAL(end()), this, SLOT(on_stopButton_pressed()));
    connect(_worker, SIGNAL(end()), this, SLOT(updateScreen()));
    connect(_worker, SIGNAL(end()), this, SLOT(log()));
    connect(_worker, SIGNAL(end()), this, SLOT(logMem()));
    connect(_worker, SIGNAL(end()), this, SLOT(updateReg()));



    connect(_worker, SIGNAL(log()), this, SLOT(updateScreenRun()));
    connect(_worker, SIGNAL(log()), this, SLOT(updateMemRun()));

    connect(ui->updateScreenButton, SIGNAL(pressed()), this, SLOT(updateScreen()));
    connect(ui->memFromSpinBox, SIGNAL(valueChanged(int)), this, SLOT(minMem(int)));
    connect(ui->plotMemButton, SIGNAL(clicked(bool)), this, SLOT(logMem()));

    connect(ui->stepsByFramesSpinBox, SIGNAL(valueChanged(int)), _worker, SLOT(setSteps(int)));

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
    if(file.size() != 0)
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
    if(_proc.loaded()){
        if(_proc.ended()){
            QMessageBox::information(this, "Ended", "You have reached the end of the program");
        }else{
            ui->goButton->setEnabled(false);
            ui->stopButton->setEnabled(true);
            _workThread->start();
        }
    }else{
        QMessageBox::critical(this, "Error", "Nothing was loaded");
    }
}

void MainWindow::on_stopButton_pressed(){
    ui->goButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    _workThread->exit();
}

void MainWindow::on_resetButton_pressed(){
    _proc.resetState();
    updateScreen();
    updateReg();
    log();
    logMem();
}

void MainWindow::logMem(){
   QString t;
    for(int i = ui->memFromSpinBox->value(); i<=ui->memToSpinBox->value(); ++i){
        t += QString::number(i,16) + QString(" : ") + QString::number(_proc.getMemory()[i], 16) + QString("\n");
   }
   ui->memTextEdit->setText(t);
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

void MainWindow::updateMemRun(){
    if(ui->updateMemCheckbox->isChecked()){
        logMem();
    }
}

void MainWindow::updateScreen(){

    for(unsigned i = 0; i < screen_height; ++i){
        for(unsigned j = 0; j < screen_width; ++j){

            word pix = _proc.getMemory()[screen_offset+i*screen_width+j];
            unsigned r = 16 * ( (pix & 0x0F00)>>8 );
            unsigned g = 16 * ( (pix & 0x00F0)>>4 );
            unsigned b = 16 * ( (pix & 0x000F)>>0 );

            QColor c(r, g, b);

            if( c != _screen.pixelColor((QPoint(screen_scale*j, screen_scale*screen_height - 1 - (screen_scale*i)))) ){
                for(unsigned x1 = 0; x1 < screen_scale; ++x1){
                    for(unsigned y1 = 0; y1 < screen_scale; ++y1){

                        _screen.setPixelColor(QPoint(screen_scale*j + x1, screen_scale*screen_height - 1 - (screen_scale*i + y1)), c);

                    }
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

void MainWindow::stop(){
    ui->goButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
//    _runthread->exit();
}

//void MainWindow::step(){
//    static int counter = 0;
//    bool fin = false;
//    for(int a = 0; a<ui->stepsByFramesSpinBox->value(); ++a){
//        if(not _proc.ended()){
//            _proc.step();
//        }else{
//            on_stopButton_pressed();
//            fin = true;
//            break;
//        }
//    }

//    if(fin){
//        log();
//        updateReg();
//        updateScreen();
//        counter = 0;
//        return;
//    }

//    updateReg();
//    log();
//    counter ++;
//    if(counter == zero_frames)
//        counter = 0;
//}

void MainWindow::minMem(int a){
    ui->memToSpinBox->setMinimum(a);
}
