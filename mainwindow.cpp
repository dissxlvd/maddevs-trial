#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "settingswindow.h"
#include "graphview.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    srand(static_cast<unsigned> (time(0)));

    GraphView *g = new GraphView(this);
    g->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(this, &MainWindow::emitPoint, g, &GraphView::recPoint);
    connect(this, &MainWindow::emitPoints, g, &GraphView::recPoints);
    connect(g, &GraphView::changeStatus, this, &MainWindow::on_taskProgress_valueChanged);
    ui->graphView->setStyleSheet("border: 1px solid red"); // @graph style sheet
    ui->graphView->layout()->addWidget(g);

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

// Pseudo-random float coordinate generator
double generateRandomFloats(){
    double lran = -1.0;
    double hran = 1.0;

    double rf = lran + static_cast<double> (rand()) / static_cast<double> (RAND_MAX / (hran - lran));
    /// Increase or decrease rf multiplier for differen results,
    /// 100 works best imo, 10 creates a grid pattern, 1000 will be too close with pen width 6
    rf = round(rf * 100) / 100;

    return rf;
}

bool checkFloats(double rf1, double rf2){
    if(rf1*rf1 + rf2*rf2 < 1){
        return true;
    } else {
        return false;
    }
}

void MainWindow::on_generatePoint_clicked() {
    double rX = generateRandomFloats();
    double rY = generateRandomFloats();

    if(checkFloats(rX, rY) == true){
        QPointF pt(rX, rY);
        emit emitPoint(pt);
    } else {
        on_generatePoint_clicked();
    }
}

void MainWindow::on_generateGraph_clicked() {
    std::vector<QPointF> ptPack;

    for(int i = 0; i < 100; ++i){
        double rX = generateRandomFloats();
        double rY = generateRandomFloats();

        if(checkFloats(rX, rY) == true){
            QPointF pt(rX, rY);
            ptPack.push_back(pt);
        } else {
            --i;
        }
    }

    emit emitPoints(ptPack);
}


void MainWindow::on_taskProgress_valueChanged(int value) {
    qDebug() << value;
    this->ui->taskProgress->setValue(value);
}

