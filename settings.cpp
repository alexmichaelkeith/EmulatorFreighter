#include "settings.h"
#include "ui_settings.h"

#include "EmulatorFreighter.h"


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    // GetInstance of UI elements

    // General Menu
    QListWidget *listWidget_ROMS = this->ui->listWidget_ROMS;
    QListWidget *listWidget_Emulators = this->ui->listWidget_Emulators;

    // Populate ROMS listWidget

    for (int i=0;i<emulatorFreighter.config.romDirectories.size();i++) {
            listWidget_ROMS->addItem(QString::fromStdString(emulatorFreighter.config.romDirectories[i]));
    }

    connect(ui->listWidget_ROMS, SIGNAL(itemClicked(QListWidgetItem*)),
        this, SLOT(onlistWidget_ROMS_ItemClicked(QListWidgetItem*)));

    // Emulators Menu

    // Populate Emulators listWidget

    listWidget_Emulators->addItem(QString::fromStdString("Add Emulator"));

    for (int i=0;i<emulatorFreighter.emulators.size();i++) {
        listWidget_Emulators->addItem(QString::fromStdString(emulatorFreighter.emulators[i].name));
    }

    connect(ui->listWidget_Emulators, SIGNAL(itemClicked(QListWidgetItem*)),
        this, SLOT(onlistWidget_Emulators_ItemClicked(QListWidgetItem*)));

}

Settings::~Settings()
{
    delete ui;
}

std::string vectorToString(std::vector<std::string> const &strings, std::string delim)
{
    std::stringstream ss;
    std::copy(strings.begin(), strings.end(),
    std::ostream_iterator<std::string>(ss, delim.c_str()));
    std::string extensionsString = ss.str();
    if (extensionsString != ""){extensionsString.pop_back();}
    return extensionsString;
}

std::vector<std::string> stringToVector(std::string extensionsString)
{
        std::vector<std::string> v;
        std::stringstream ss(extensionsString);
        while (ss.good()) {
            std::string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }
     return v;
}

void Settings::on_buttonBox_accepted()
{
    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    // Save all settings
    emulatorFreighter.writeConfig();
    emulatorFreighter.writeEmulators();
    emulatorFreighter.writeRoms();

}


void Settings::on_pushButton_AddROM_clicked()
{
    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QListWidget *listWidget_ROMS = this->ui->listWidget_ROMS;


    // Create instances of UI components
    QLineEdit *lineEdit = this->ui->lineEdit_NewRom;

    if (lineEdit->text().toStdString() != "") {
        emulatorFreighter.config.romDirectories.push_back(lineEdit->text().toStdString());
        listWidget_ROMS->addItem(lineEdit->text());
    }
}

void Settings::onlistWidget_ROMS_ItemClicked(QListWidgetItem* item)
{
    romDirectorySelected = item;
}

void Settings::onlistWidget_Emulators_ItemClicked(QListWidgetItem* item)
{

    emulatorSelected = item;

    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QLineEdit *lineEdit_Name = this->ui->lineEdit_Name;
    QLineEdit *lineEdit_Extensions =  this->ui->lineEdit_Extensions;
    QLineEdit *lineEdit_Path =  this->ui->lineEdit_Path;
    QLineEdit *lineEdit_Mid =  this->ui->lineEdit_Mid;
    QLineEdit *lineEdit_End =  this->ui->lineEdit_End;

    for (int i=0;i<=emulatorFreighter.roms.size();i++){
        if(emulatorFreighter.emulators[i].name == emulatorSelected->text().toStdString()) {
            lineEdit_Name->setText(QString::fromStdString(emulatorFreighter.emulators[i].name));
            lineEdit_Extensions->setText(QString::fromStdString(vectorToString(emulatorFreighter.emulators[i].extensions,",")));
            lineEdit_Path->setText(QString::fromStdString(emulatorFreighter.emulators[i].path));
            lineEdit_Mid->setText(QString::fromStdString(emulatorFreighter.emulators[i].midParameters));
            lineEdit_End->setText(QString::fromStdString(emulatorFreighter.emulators[i].trailingParameters));
        }
     }
    if("Add Emulator" == emulatorSelected->text().toStdString()) {

        lineEdit_Name->setText(QString::fromStdString(""));
        lineEdit_Extensions->setText(QString::fromStdString(""));
        lineEdit_Path->setText(QString::fromStdString(""));
        lineEdit_Mid->setText(QString::fromStdString(""));
        lineEdit_End->setText(QString::fromStdString(""));

    }
}

void Settings::on_pushButtonRemoveROM_clicked()
{

    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QListWidget *listWidget_ROMS = this->ui->listWidget_ROMS;


    for(int i=0;i<=emulatorFreighter.config.romDirectories.size();i++){
        if(romDirectorySelected->text().toStdString() == emulatorFreighter.config.romDirectories[i]) {
            emulatorFreighter.config.romDirectories.erase(emulatorFreighter.config.romDirectories.begin() + i);
            // Remove item from list

            // Below line crashes system?
            delete ui->listWidget_ROMS->takeItem(ui->listWidget_ROMS->row(romDirectorySelected));
        }
    }
}


void Settings::on_pushButton_DeleteEmulator_clicked()
{
    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QListWidget *listWidget_Emulators = this->ui->listWidget_Emulators;

    for(int i=0;i<=emulatorFreighter.emulators.size();i++){
        if(emulatorSelected->text().toStdString() == emulatorFreighter.emulators[i].name && emulatorSelected->text().toStdString() != "Add Emulator") {
            emulatorFreighter.emulators.erase(emulatorFreighter.emulators.begin() + i);
            // Remove item from list
            delete ui->listWidget_Emulators->takeItem(ui->listWidget_Emulators->row(emulatorSelected));
        }
    }
}


void Settings::on_pushButton_EmulatorAddSave_clicked()
{

    // GetInstance of emulator Freighter
    EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();

    QLineEdit *lineEdit_Name = this->ui->lineEdit_Name;
    QLineEdit *lineEdit_Extensions =  this->ui->lineEdit_Extensions;
    QLineEdit *lineEdit_Path =  this->ui->lineEdit_Path;
    QLineEdit *lineEdit_Mid =  this->ui->lineEdit_Mid;
    QLineEdit *lineEdit_End =  this->ui->lineEdit_End;

    QListWidget *listWidget_Emulators = this->ui->listWidget_Emulators;


    if (emulatorSelected->text().toStdString() == "Add Emulator" && lineEdit_Name->text().toStdString() != "") {

        // Create new Emulator
        EmulatorFreighter::Emulator newEmulator(lineEdit_Name->text().toStdString(),
            stringToVector(lineEdit_Extensions->text().toStdString()),
            lineEdit_Path->text().toStdString(),
            lineEdit_Mid->text().toStdString(),
            lineEdit_End->text().toStdString());
        listWidget_Emulators->addItem(QString::fromStdString(lineEdit_Name->text().toStdString()));
    }
    else if(emulatorSelected->text().toStdString() != "Add Emulator" && lineEdit_Name->text().toStdString() != ""){

        for (int i=0;i<=emulatorFreighter.roms.size();i++){
            if(emulatorFreighter.emulators[i].name == lineEdit_Name->text().toStdString() && lineEdit_Name->text().toStdString() != "") {
                emulatorFreighter.emulators[i].path = lineEdit_Path->text().toStdString();
                emulatorFreighter.emulators[i].extensions = stringToVector(lineEdit_Extensions->text().toStdString());
                emulatorFreighter.emulators[i].midParameters = lineEdit_Mid->text().toStdString();
                emulatorFreighter.emulators[i].trailingParameters = lineEdit_End->text().toStdString();
                emulatorFreighter.writeEmulators();
            }
        }

    }
}

