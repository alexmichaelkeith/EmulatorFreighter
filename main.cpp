#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialize QApplication
    QApplication app(argc, argv);

    // Initialize Main Window
    MainWindow *mainWindow = new MainWindow;



    mainWindow->setCentralWidget(scrollArea);


    // Execute QApplication
    return app.exec();
}
