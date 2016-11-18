#include "widget.hpp"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_runButton_pressed(){
//    try{
//        proc->run(interative);
//    }catch(std::string s){
//        cerr << s << endl;
//        return 1;
//    }catch(std::exception e){
//        cerr << e.what() << endl;
//        return 1;
//    }

}
