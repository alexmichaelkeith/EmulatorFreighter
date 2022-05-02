#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include <QListWidgetItem>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_AddROM_clicked();

    void on_pushButtonRemoveROM_clicked();

    void onlistWidget_ROMS_ItemClicked(QListWidgetItem* item);

    void onlistWidget_Emulators_ItemClicked(QListWidgetItem* item);

    void on_pushButton_DeleteEmulator_clicked();

    void on_pushButton_EmulatorAddSave_clicked();

private:
    Ui::Settings *ui;

    QListWidgetItem *emulatorSelected;

    QListWidgetItem *romDirectorySelected;

};

#endif // SETTINGS_H
