#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <QApplication>

#include "widget.hpp"

/// \warning Ceci va être impossible à comprendre


using namespace std;


int main(int argc, char** argv)
{

     QApplication app(argc, argv);
     Widget *w = new Widget();

     w->show();

     return app.exec();
}
