#include "mainwindow.h"
#include <QApplication>
#include "EmulatorFreighter.h"
#include "Scrape.h"

int main(int argc, char *argv[])
{
    // Get instance of Emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();
    // Scan Roms
    emulatorFreighter.scanRoms();
    // Create MainWindow
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow;
    // execute app
    return app.exec();
}
