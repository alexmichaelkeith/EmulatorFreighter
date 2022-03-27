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

#include <quickScanner.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <structures.h>
#include <map>

#include <functions.h>
#include <QResizeEvent>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    config myConfig;
    myConfig = readConfig();

    quickScanner myscanner;

    vector<rom> romVector;
    romVector = myscanner.scanRoms(myConfig);

    outputRoms(romVector);
    outputConfig(myConfig);

    QApplication app(argc, argv);

    QGridLayout *gridLayout = new QGridLayout;
    // addWidget(*Widget, row, column, rowspan, colspan)



    int romcount = romVector.size() - 1;
    int row = 0;
    int romsperrow = 5;
    string name;
    while (romcount > 0) {

        for (int j = 0;j<romsperrow;j++) {
            name = romVector[romcount].filename;
            QToolButton *name = new QToolButton();
            name->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            name->setStyleSheet("font: Georgia;font-size: 12px;font: Bold;font: white;background-color: rgba(255, 255, 255, 0);color: #FFFFFF;");
            name->setText(findName(romVector[romcount]).c_str());
            name->setMinimumWidth(264);
            name->setMinimumHeight(400);
            name->setMaximumWidth(264);
            name->setMaximumHeight(400);
            name->setIcon(QIcon(findImage(romVector[romcount]).c_str()));
            name->setIconSize(QSize(264, 352));
            QObject::connect(name, &QToolButton::clicked, [=]()
            {
                cout << romVector[romcount].runpath.c_str() << endl;
                system(romVector[romcount].runpath.c_str());




                   });

            gridLayout->addWidget(name,row,j,1,1);

            if (romcount == 0) {break;}
            romcount --;
        }
        row++;
    }

    MainWindow *mainWindow = new MainWindow;

    // Create a widget
    QWidget *w = new QWidget(mainWindow);
    mainWindow->setCentralWidget(w);
    // Set the grid layout as a main layout
    w->setLayout(gridLayout);
    // Window title and background
    mainWindow->setWindowTitle("Emulator Freightor");
    w->setStyleSheet("background-image: url(config/images/gradient.jpg);");
    // Display
    mainWindow->showMaximized();
    // Event loop
    return app.exec();
}
