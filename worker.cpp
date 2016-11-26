#include "worker.hpp"

Worker::Worker(Processor* proc, int steps, QObject *parent) : QObject(parent), _proc(proc), _run(true), _steps(steps)
{
    connect(_proc, SIGNAL(finished()), this, SLOT(stop()));
}

void Worker::start(){
    _run = true;
    int i = 0;
    while(_run){
        if(i >= _steps){
            i = 0;
            emit log();
        }else{
            ++i;
        }
        _proc->step();
    }
    emit end();
}

void Worker::stop(){
    _run = false;
}
