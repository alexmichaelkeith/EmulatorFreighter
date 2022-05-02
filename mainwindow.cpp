#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QTimerEvent>

#include "EmulatorFreighter.h"

#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QToolButton>


#include <iostream>

#include <settings.h>


#include <iostream>

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if (timerId){
        killTimer(timerId);
        timerId = 0;
    }
    timerId = startTimer(500/*delay beetween ends of resize and your action*/);

}


QGridLayout* renderGridLayout(int tilesPerScreen)
{

    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QGridLayout *gridLayout = new QGridLayout;
    // addWidget(*Widget, row, column, rowspan, colspan)

    int romcount = emulatorFreighter.roms.size() - 1;
    int row = 0;
    string name;

    int column = 0;
    for (int i=0;i<=romcount;i++) {
        name = emulatorFreighter.roms[i].filename;
        QToolButton *name = new QToolButton();
        name->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        name->setStyleSheet("font: Open Sans;font-size: 12px;font: Bold;font: white;background-color: rgba(255, 255, 255, 0);color: #000000;");
        name->setText(emulatorFreighter.findName(emulatorFreighter.roms[i]).c_str());
        name->setMinimumWidth(emulatorFreighter.config.tileWidth);
        name->setMinimumHeight(emulatorFreighter.config.tileHeight + (emulatorFreighter.config.tileHeight / 10));
        name->setMaximumWidth(emulatorFreighter.config.tileWidth);
        name->setMaximumHeight(emulatorFreighter.config.tileHeight + (emulatorFreighter.config.tileHeight / 10));
        name->setIcon(QIcon(emulatorFreighter.findImage(emulatorFreighter.roms[i]).c_str()));
        name->setIconSize(QSize(emulatorFreighter.config.tileWidth, emulatorFreighter.config.tileHeight));

        string runPath = emulatorFreighter.roms[i].runpath;

        QObject::connect(name, &QToolButton::clicked, [=]()
        {
            system(runPath.c_str());
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


void renderMainWindow(MainWindow *mainWindow){

    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();


    int tilesPerScreen;
    int screenSize = mainWindow->size().width();
    tilesPerScreen = floor(screenSize / (emulatorFreighter.config.tileWidth));

    QWidget *w = new QWidget(mainWindow);
    QGridLayout *gridLayout = renderGridLayout(tilesPerScreen);


    QScrollArea* scrollArea = new QScrollArea;

    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( w );


    mainWindow->setCentralWidget(scrollArea);
    scrollArea->setWidget(w);


    w->setLayout(gridLayout);
    scrollArea->verticalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->hide();
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scrollArea->setFrameShape(QFrame::NoFrame);

}

void renderMetaData(){

    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();






}

void MainWindow::timerEvent(QTimerEvent *te) {

    renderMainWindow(this);
    killTimer(te->timerId());
    timerId = 0;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderMainWindow(this);
    this->setWindowTitle("Emulator Freighter");
    this->show();

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionSettings_triggered()
{
    Settings settings;
    settings.setModal(true);
    settings.exec();
}


