#include "mainwindow.h"
#include <QApplication>
#include "EmulatorFreighter.h"
//#include "Scrape.h"
#include <thread>
#include <QEventLoop>

#include "Scrape.h"

#include <QFutureWatcher>

#include <QFuture>

#include <QtConcurrent>

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

    // Scrape ROMS

    // Instantiate the objects and connect to the finished signal.
    //MyClass myObject;
    QFutureWatcher<int> watcher;
    MainWindow::connect(&watcher, SIGNAL(finished()), mainWindow, SLOT(handleFinished()));

    bool needScrape = false;
    for(int i=0;i<=emulatorFreighter.roms.size();i++) {

        if (emulatorFreighter.roms[i].nameIGDB == "") {
            needScrape = true;
        }
    }

    if (needScrape == true){
    // Scrape ROMS in seperate thread
    QFuture<int> future = QtConcurrent::run(scrapeROMS);
    watcher.setFuture(future);
    }

    return app.exec();
}
