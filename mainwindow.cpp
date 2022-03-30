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
#include <QTimer>
#include <QTimerEvent>

// declare prototypes
QGridLayout* renderMainWindow(int tilesPerScreen);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget(this);

    config myConfig;
    myConfig = readConfig();


    int tilesPerScreen;
    int screenSize = this->size().width();
    tilesPerScreen = floor(screenSize / (myConfig.tileWidth));


    QScrollArea* scrollArea = new QScrollArea;

    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( w );



    QGridLayout *gridLayout = renderMainWindow(tilesPerScreen);

    this->setCentralWidget(scrollArea);
    scrollArea->setWidget(w);


    w->setLayout(gridLayout);

    //this->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                        //"background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 black, stop:1 grey);}");

    //this->setStyleSheet("background-image: url(config/images/cf.svg);");

    scrollArea->verticalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scrollArea->setFrameShape(QFrame::NoFrame);




    this->setWindowTitle("Emulator Freightor");
    this->show();


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    int timerId = 0;

    if (timerId){
        killTimer(timerId);
        timerId = 0;
    }
    timerId = startTimer(500/*delay beetween ends of resize and your action*/);

}




void MainWindow::timerEvent(QTimerEvent *te) {


    int timerId = 0;

    config myConfig;
    myConfig = readConfig();


    int tilesPerScreen;
    int screenSize = this->size().width();
    tilesPerScreen = floor(screenSize / (myConfig.tileWidth));

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


    killTimer(te->timerId());
    timerId = 0;

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
                name->setMinimumWidth(myConfig.tileWidth);
                name->setMinimumHeight(myConfig.tileHeight + (myConfig.tileHeight / 10));
                name->setMaximumWidth(myConfig.tileWidth);
                name->setMaximumHeight(myConfig.tileHeight + (myConfig.tileHeight / 10));
                name->setIcon(QIcon(findImage(romVector[romcount]).c_str()));
                name->setIconSize(QSize(myConfig.tileWidth, myConfig.tileHeight));
                QObject::connect(name, &QToolButton::clicked, [=]()
                {
                    cout << romVector[romcount].runpath.c_str() << endl;
                    system(romVector[romcount].runpath.c_str());
                       });

                gridLayout->addWidget(name,row,column,1,1,{Qt::AlignTop, Qt::AlignLeft});

                gridLayout->setContentsMargins(0, 0, 0, 0);

                gridLayout->setSizeConstraint(QLayout::SetFixedSize);
                gridLayout->setVerticalSpacing(0);
                gridLayout->setHorizontalSpacing(10);


    column++;
    if (column==tilesPerScreen-1){
        column = 0;
        row++;
    }
}
    return(gridLayout);
}
