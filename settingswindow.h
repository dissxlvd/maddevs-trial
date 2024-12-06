#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    // bool get_themeCheck();
    // void set_themeCheck(bool new_themeCheck);

private slots:
    void on_toolButton_toggled(bool checked);

private:
    // bool themeCheck;
    Ui::SettingsWindow *ui;

signals:
    void changeThemeSignal(bool sig);
};

#endif // SETTINGSWINDOW_H
