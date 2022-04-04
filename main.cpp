#include <QApplication>
#include <mainwindow.h>
#include "quickScanner.h"


int main(int argc, char *argv[])
{
    // Initialize QApplication
    QApplication app(argc, argv);

    // Initialize Main Window
    MainWindow *mainWindow = new MainWindow;


    //threadingtest();



    // Execute QApplication
    return app.exec();
}



