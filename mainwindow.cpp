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
#include "Python.h"
#include<thread>


// declare prototypes
QGridLayout* renderMainWindow(int tilesPerScreen);
void threadingTest(vector<rom> romVector);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget(this);

    config myConfig;
    myConfig = readConfig();

    quickScanner myscanner;

    vector<rom> romVector;
    romVector = myscanner.scanRoms(myConfig);


    int tilesPerScreen;
    int screenSize = this->size().width();
    tilesPerScreen = floor(screenSize / (myConfig.tileWidth));


    QScrollArea* scrollArea = new QScrollArea;

    scrollArea->setWidgetResizable( true );

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

    // threading metadata
    threadingTest(romVector);

    //relog
    gridLayout = renderMainWindow(tilesPerScreen);
    this->setCentralWidget(scrollArea);
    scrollArea->setWidget(w);
    w->setLayout(gridLayout);

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
    MainWindow* mainWindow;
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

void threadingTest(vector<rom> romVector) {

    vector<rom> metaQueue;
    string funcName = "metadata";
    string query = "test";

    bool flag = true;
    while (flag == true) {
        flag = false;
        for(int i=0;i<romVector.size();i++){

            // If any roms are found without image or invalid image call python scanner and flag that another loop is needed
            if (romVector[i].imagePathIGDB == "" || !exists(romVector[i].imagePathIGDB)){
                //flag = true;

                // Call Python to scrape three roms

                char* procname = new char[funcName.length() + 1];
                strcpy(procname, funcName.c_str());

                char* paramval = new char[query.length() + 1];
                strcpy(paramval, query.c_str());

                PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
                // Initialize the Python Interpreter
                Py_Initialize();
                // Build the name object
                pName = PyUnicode_FromString((char*)"scrapeIGDB");
                // Load the module object
                pModule = PyImport_Import(pName);
                // pDict is a borrowed reference
                pDict = PyModule_GetDict(pModule);
                // pFunc is also a borrowed reference
                pFunc = PyDict_GetItemString(pDict, procname);
                if (PyCallable_Check(pFunc))
                {
                    pValue = Py_BuildValue("(z)", paramval);
                    PyErr_Print();
                    presult = PyObject_CallObject(pFunc, pValue);
                    PyErr_Print();
                }
                else
                {
                    PyErr_Print();
                }
                //printf("Result is %d\n", _PyUnicode_AsString(presult));
                Py_DECREF(pValue);
                // Clean up
                Py_DECREF(pModule);
                Py_DECREF(pName);
                // Finish the Python Interpreter
                Py_Finalize();

                // clean
                delete[] procname;
                delete[] paramval;

                // Get Python return
                //return _PyUnicode_AsString(presult);
            }
        }
        // reload mainWindow
    }
}

