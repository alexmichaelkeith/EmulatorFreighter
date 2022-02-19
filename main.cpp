#include "mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QToolButton>

#include <quickScanner.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <structures.h>
#include <map>

#include <functions.h>
#include <CustomButton.h>

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

    while (romcount > 0) {

        for (int j = 0;j<romsperrow;j++) {
            QToolButton *tile = new QToolButton();
            tile->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            tile->setStyleSheet("font: Georgia;font-size: 12px;font: Bold;font: white;background-color: rgba(255, 255, 255, 0);color: #FFFFFF;");
            tile->setText(findName(romVector[romcount]).c_str());
            tile->setMinimumWidth(264);
            tile->setMinimumHeight(400);
            tile->setMaximumWidth(264);
            tile->setMaximumHeight(400);
            tile->setIcon(QIcon(findImage(romVector[romcount]).c_str()));
            tile->setIconSize(QSize(264, 352));

            QObject::connect(tile, &QToolButton::clicked, [=]()
            {
                cout << romVector[romcount].runpath.c_str() << endl;
                system(romVector[romcount].runpath.c_str());
                   });

            gridLayout->addWidget(tile,row,j,1,1);

            if (romcount == 0) {break;}
            romcount --;
        }
        row++;
    }

    // Create a widget
    QWidget *w = new QWidget();
    // Set the grid layout as a main layout
    w->setLayout(gridLayout);
    // Window title and background
    w->setWindowTitle("Emulator Freightor");
    w->setStyleSheet("background-image: url(config/images/gradient.jpg);");
    // Display
    w->showMaximized();
    // Event loop
    return app.exec();
}
