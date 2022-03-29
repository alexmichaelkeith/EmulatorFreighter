#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QGridLayout>
#include <structures.h>
#include <vector>
#include <quickScanner.h>
#include <QToolButton>
#include <QScrollArea>
#include <QScrollBar>
#include <iostream>
// declare prototypes
QGridLayout* renderMainWindow(int tilesPerScreen);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget(this);

    int tilesPerScreen;
    int screenSize = this->size().width();
    int tileWidth = 264;
    int tilePadding = 36;
    tilesPerScreen = floor(screenSize / (tileWidth + tilePadding));


    QScrollArea* scrollArea = new QScrollArea;

    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( w );



    QGridLayout *gridLayout = renderMainWindow(tilesPerScreen);

    this->setCentralWidget(scrollArea);
    scrollArea->setWidget(w);


    w->setLayout(gridLayout);

    //this->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                        //"background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey);}");

    //this->setStyleSheet("background-image: url(config/images/comb.svg);");
    this->setWindowTitle("Emulator Freightor");
    this->showMaximized();
    scrollArea->verticalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scrollArea->setFrameShape(QFrame::NoFrame);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   int tilesPerScreen;
   int screenSize = this->size().width();
   int tileWidth = 264;
   int tilePadding = 36;
   tilesPerScreen = floor(screenSize / (tileWidth + tilePadding));

   QWidget *w = new QWidget(this);
   QGridLayout *gridLayout = renderMainWindow(tilesPerScreen);


   QScrollArea* scrollArea = new QScrollArea;

   scrollArea->setWidgetResizable( true );
   scrollArea->setWidget( w );


   this->setCentralWidget(scrollArea);
   scrollArea->setWidget(w);


   w->setLayout(gridLayout);
   scrollArea->verticalScrollBar()->hide();
   scrollArea->horizontalScrollBar()->hide();
   scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
   scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
   scrollArea->setFrameShape(QFrame::NoFrame);

}

void clearMainWidget()
{


}

void setMainWidget()
{



}

QGridLayout* renderMainWindow(int tilesPerScreen)
{
    config myConfig;
    myConfig = readConfig();
    quickScanner myscanner;

    vector<rom> romVector;
    romVector = myscanner.scanRoms(myConfig);

    outputRoms(romVector);
    outputConfig(myConfig);

    QGridLayout *gridLayout = new QGridLayout;
    // addWidget(*Widget, row, column, rowspan, colspan)

    int romcount = romVector.size() - 1;
    int row = 0;
    string name;

    int column = 0;


    for (int i=0;i<=romcount;i++) {

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

                gridLayout->addWidget(name,row,column,1,1);


    column++;
    if (column==tilesPerScreen-1){
        column = 0;
        row++;
    }
}

    return(gridLayout);
}
