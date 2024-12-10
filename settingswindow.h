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

private slots:
    void on_toolButton_toggled(bool checked);

    void on_toolButton_2_clicked();

private:
    Ui::SettingsWindow *ui;
    bool debugEnabled;

signals:
    void changeThemeSignal(bool sig);
    void enableDebugMenu(bool debugEnabled);
};

#endif // SETTINGSWINDOW_H
