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
float generateRandomFloats(){
    float lran = -1.0;
    float hran = 1.0;

    float rf = lran + static_cast<float> (rand()) / static_cast<float> (RAND_MAX / (hran - lran));
    /// Increase or decrease rf multiplier for differen results,
    /// 100 works best imo, 10 creates a grid pattern, 1000 will be too close with pen width 6
    rf = round(rf * 100) / 100;

    return rf;
}

bool checkFloats(float rf1, float rf2){
    if(rf1*rf1 + rf2*rf2 < 1){
        return true;
    } else {
        return false;
    }
}

void MainWindow::on_generatePoint_clicked() {
    float rX = generateRandomFloats();
    float rY = generateRandomFloats();

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
        float rX = generateRandomFloats();
        float rY = generateRandomFloats();

        if(checkFloats(rX, rY) == true){
            QPointF pt(rX, rY);
            ptPack.push_back(pt);
        } else {
            --i;
        }
    }

    emit emitPoints(ptPack);
}

