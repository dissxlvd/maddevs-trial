#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public slots:
    void changeThemeSlot(bool checked);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionApp_Settings_triggered();

    void on_generatePoint_clicked();

    void on_generateGraph_clicked();

    void on_taskProgress_valueChanged(int value);

    void enableDebugMenu(bool debugEnabled);

    void showLegend(bool pathsGenerated);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    int pointsQty = 100;

signals:
    void emitPoint(QPointF pt);
    void emitPoints(std::vector<QPointF> ptPack);
};
#endif // MAINWINDOW_H
