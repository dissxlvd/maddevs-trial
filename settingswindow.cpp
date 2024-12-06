#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
    qDebug() << "Called settingswindow constructor";
    ui->setupUi(this);

    // Settings
    this->setWindowFlag(Qt::Window);
    this->setWindowTitle("MadDevs | App Settings");
    this->setMinimumSize(320, 400);
    this->resize(320, 400);
}

SettingsWindow::~SettingsWindow() {
    qDebug() << "Called settingswindow destructor";
    delete ui;
}

void SettingsWindow::on_toolButton_toggled(bool checked) {
    qDebug() << checked;
    emit changeThemeSignal(checked);
}
