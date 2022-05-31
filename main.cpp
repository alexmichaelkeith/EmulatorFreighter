#include "mainwindow.h"
#include <QApplication>
#include "EmulatorFreighter.h"
//#include "Scrape.h"
#include <thread>

#include "Scrape.h"

int main(int argc, char *argv[])
{
    // Get instance of Emulator Freighter



    // Scan Roms
    //emulatorFreighter.scanRoms();

    // Scan ROMS
    //std::thread t(&EmulatorFreighter::scanRoms, EmulatorFreighter::getInstance());


    // Create MainWindow
    QApplication app(argc, argv);
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    // Scan Roms
    emulatorFreighter.scanRoms();

    // Create MainWindow
    MainWindow *mainWindow = new MainWindow;

    // Scrape Roms
    std::thread t(scrapeROMS, mainWindow);

    //MainWindow* mainWindow = emulatorFreighter.mainWindow;
    // execute app
    return app.exec();
}
