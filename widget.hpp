#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>

#include <QWidget>

#include "processor.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void on_runButton_pressed();

private:
    std::unique_ptr<Processor> _proc;
    Ui::Widget *ui;
};

#endif // WIDGET_HPP
