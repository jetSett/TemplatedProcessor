#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "processor.hpp"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(Processor* proc, int steps, QObject *parent = 0);

signals:
    void log();
    void end();

public slots:
    void start();
    void stop();
    void setSteps(int s){
        _steps = s;
    }

private:
    bool _run;
    Processor *_proc;
    int _steps;
};

#endif // WORKER_H
