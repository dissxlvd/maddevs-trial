#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "settingswindow.h"
#include "graphview.h"
#include "graph.h"
#include "point.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    GraphView *g = new GraphView(this);
    ui->graph->setStyleSheet("border: 1px solid red"); // @graph style sheet
    ui->graph->layout()->addWidget(g);

    // Settings
    this->setWindowTitle("MadDevs | Trial Assignment");
    this->setMinimumSize(800, 600);
    this->resize(800, 600);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeThemeSlot(bool checked){
    if(checked == true){
        ui->centralwidget->setPalette(QPalette(QColor(48, 50, 51)));
    } else {
        ui->centralwidget->setPalette(QPalette(QColor(230, 238, 242)));
    }
}

void MainWindow::on_actionApp_Settings_triggered() {
    SettingsWindow *s = new SettingsWindow(this);
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(s, &SettingsWindow::changeThemeSignal, this, &MainWindow::changeThemeSlot);
    s->show();
}


void MainWindow::on_generatePoint_clicked()
{
    Point *p = new Point();
    p->_test();

    delete p;
}

