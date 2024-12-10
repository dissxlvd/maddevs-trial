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

    void on_pointsQty_valueChanged(int pointsQty);

    void on_spPos_valueChanged(int startPosition);

    void on_epPos_valueChanged(int arg1);

    void on_findPath_clicked();

private:
    Ui::MainWindow *ui;

    int pointsQty = 100;

    int sp = 0;
    int ep = 99;

signals:
    void emitStartPosition(int startPosition);
    void emitEndPosition(int endPosition);

    void emitPoint(QPointF pt);
    void emitPoints(std::vector<QPointF> ptPack);

    void tryToFindPathSignal();
};
#endif // MAINWINDOW_H
