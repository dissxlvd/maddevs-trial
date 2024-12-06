#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    /// Main Window
    QApplication a(argc, argv);
    MainWindow w;

    /// Widgets
    QPalette darkModePalette = QPalette(QColor(48, 50, 51));

    w.centralWidget()->setAutoFillBackground(true);
    w.centralWidget()->setPalette(darkModePalette); // Dark Mode Color

    w.show();
    return a.exec();
}
