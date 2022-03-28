#include "mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QToolButton>
#include <QMenuBar>
#include <QVBoxLayout>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include <QResizeEvent>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{


    QApplication app(argc, argv);



    MainWindow *mainWindow = new MainWindow;

    // Create a widget
    // Set the grid layout as a main layout
    //w->setLayout(gridLayout);
    // Window title and background
    //w->setStyleSheet("background-image: url(config/images/gradient.jpg);");
    // Display
    // Event loop
    return app.exec();
}
