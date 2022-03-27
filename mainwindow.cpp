#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   int size = this->size().width();
   size = floor(size / 264);
   std::cout << (std::to_string(size)) << std::endl;
}
