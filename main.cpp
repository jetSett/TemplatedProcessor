#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <QApplication>

#include "mainwindow.hpp"

/// \warning Ceci va être impossible à comprendre


using namespace std;


int main(int argc, char** argv)
{

     QApplication app(argc, argv);
     MainWindow w;

     w.show();

     return app.exec();
}
