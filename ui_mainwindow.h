/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRefresh_All;
    QAction *actionMetadata;
    QAction *actionEmulators;
    QAction *actionSmall;
    QAction *actionMedium;
    QAction *actionLarge;
    QAction *actionName;
    QAction *actionDate;
    QAction *actionIGDB_Score;
    QAction *actionExit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuIcons;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionRefresh_All = new QAction(MainWindow);
        actionRefresh_All->setObjectName(QString::fromUtf8("actionRefresh_All"));
        actionMetadata = new QAction(MainWindow);
        actionMetadata->setObjectName(QString::fromUtf8("actionMetadata"));
        actionEmulators = new QAction(MainWindow);
        actionEmulators->setObjectName(QString::fromUtf8("actionEmulators"));
        actionSmall = new QAction(MainWindow);
        actionSmall->setObjectName(QString::fromUtf8("actionSmall"));
        actionSmall->setCheckable(true);
        actionMedium = new QAction(MainWindow);
        actionMedium->setObjectName(QString::fromUtf8("actionMedium"));
        actionMedium->setCheckable(true);
        actionMedium->setChecked(true);
        actionLarge = new QAction(MainWindow);
        actionLarge->setObjectName(QString::fromUtf8("actionLarge"));
        actionLarge->setCheckable(true);
        actionName = new QAction(MainWindow);
        actionName->setObjectName(QString::fromUtf8("actionName"));
        actionName->setCheckable(true);
        actionName->setChecked(true);
        actionDate = new QAction(MainWindow);
        actionDate->setObjectName(QString::fromUtf8("actionDate"));
        actionDate->setCheckable(true);
        actionIGDB_Score = new QAction(MainWindow);
        actionIGDB_Score->setObjectName(QString::fromUtf8("actionIGDB_Score"));
        actionIGDB_Score->setCheckable(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuIcons = new QMenu(menuView);
        menuIcons->setObjectName(QString::fromUtf8("menuIcons"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionExit);
        menuView->addAction(menuIcons->menuAction());
        menuView->addAction(actionName);
        menuView->addAction(actionDate);
        menuView->addAction(actionIGDB_Score);
        menuIcons->addAction(actionSmall);
        menuIcons->addAction(actionMedium);
        menuIcons->addAction(actionLarge);
        menuSettings->addAction(actionMetadata);
        menuSettings->addAction(actionEmulators);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRefresh_All->setText(QCoreApplication::translate("MainWindow", "Refresh All", nullptr));
        actionMetadata->setText(QCoreApplication::translate("MainWindow", "Metadata", nullptr));
        actionEmulators->setText(QCoreApplication::translate("MainWindow", "Emulators", nullptr));
        actionSmall->setText(QCoreApplication::translate("MainWindow", "Small", nullptr));
        actionMedium->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        actionLarge->setText(QCoreApplication::translate("MainWindow", "Large", nullptr));
        actionName->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        actionDate->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        actionIGDB_Score->setText(QCoreApplication::translate("MainWindow", "IGDB Score", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuIcons->setTitle(QCoreApplication::translate("MainWindow", "Tile Sizes", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
