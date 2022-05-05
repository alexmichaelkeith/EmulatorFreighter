#include "mainwindow.h"

#include <QApplication>


#include "EmulatorFreighter.h"


#include <iostream>

#include <filesystem>

int main(int argc, char *argv[])
{

    // Get instance of Emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    // Scan Roms
    emulatorFreighter.scanRoms();

    // Create MainWindow
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow;

    return app.exec();


}
