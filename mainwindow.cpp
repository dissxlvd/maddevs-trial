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

    // Send
    connect(this, &MainWindow::emitPoint, g, &GraphView::recPoint); // Sends 1 point to graph renderer
    connect(this, &MainWindow::emitPoints, g, &GraphView::recPoints); // Sends point pack to graph renderer

    connect(this, &MainWindow::emitStartPosition, g, &GraphView::recStartPosition); // Sends point pack to graph renderer
    connect(this, &MainWindow::emitEndPosition, g, &GraphView::recEndPosition); // Sends point pack to graph renderer

    connect(this, &MainWindow::tryToFindPathSignal, g, &GraphView::tryToFindPathSlot);

    // Recieve
    connect(g, &GraphView::changeStatus, this, &MainWindow::on_taskProgress_valueChanged);
    connect(g, &GraphView::showLegend, this, &MainWindow::showLegend);

    // ui->graphView->setStyleSheet("border: 1px solid red"); // @graph style sheet
    ui->graphView->layout()->addWidget(g);

    // Hiding currently unavailable ui elements
    ui->debugMenu->hide();
    ui->graphLegend->hide();
    ui->findPath->hide();
    ui->showSummary->hide();
    ui->spLabel->hide();
    ui->spPos->hide();
    ui->epLabel->hide();
    ui->epPos->hide();

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

void MainWindow::enableDebugMenu(bool debugEnabled){
    qDebug() << debugEnabled;
    if(debugEnabled){
        this->ui->debugMenu->show();
    } else {
        this->ui->debugMenu->hide();
    }
}

void MainWindow::on_actionApp_Settings_triggered() {
    SettingsWindow *s = new SettingsWindow(this);
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(s, &SettingsWindow::changeThemeSignal, this, &MainWindow::changeThemeSlot);
    connect(s, &SettingsWindow::enableDebugMenu, this, &MainWindow::enableDebugMenu);
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

    for(int i = 0; i < this->pointsQty; ++i){
        double rX = generateRandomFloats();
        double rY = generateRandomFloats();

        if(checkFloats(rX, rY) == true){
            QPointF pt(rX, rY);
            ptPack.push_back(pt);
        } else {
            --i;
        }
    }

    this->ui->epPos->setValue(this->ep);

    emit emitPoints(ptPack);
}

void MainWindow::on_taskProgress_valueChanged(int value) {
    // qDebug() << value;
    this->ui->taskProgress->setValue(value);
}

void MainWindow::showLegend(bool pathsGenerated){
    if(pathsGenerated){
        this->ui->startingPointTip->setStyleSheet("color: #00C800");
        this->ui->endingPointTip->setStyleSheet("color: #C80000");

        this->ui->spLabel->show();
        this->ui->spPos->show();
        this->ui->epLabel->show();
        this->ui->epPos->show();

        this->ui->graphLegend->show();
        this->ui->findPath->show();
    } else {
        this->ui->graphLegend->hide();
    }
}

void MainWindow::on_pointsQty_valueChanged(int pointsQty){
    this->pointsQty = pointsQty;

    this->ui->spPos->setMaximum(pointsQty - 1);
    this->ui->epPos->setMaximum(pointsQty - 1);
}

void MainWindow::on_spPos_valueChanged(int startPosition){
    this->sp = startPosition;
    emit emitStartPosition(startPosition);
}

void MainWindow::on_epPos_valueChanged(int endPosition){
    this->ep = endPosition;
    emit emitEndPosition(endPosition);
}


void MainWindow::on_findPath_clicked(){
    emit tryToFindPathSignal();
}

