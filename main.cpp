#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Initialize QApplication
    QApplication app(argc, argv);

    // Initialize Main Window
    MainWindow *mainWindow = new MainWindow;

    // Execute QApplication
    return app.exec();
}
