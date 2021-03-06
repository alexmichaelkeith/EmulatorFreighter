#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public:
    void renderMainWindow(MainWindow *mainWindow);

private slots:
    void on_actionSettings_triggered();
    void handleFinished();

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent*);
    void timerEvent(QTimerEvent *te);


private:
    int timerId = 0;
};
#endif // MAINWINDOW_H
