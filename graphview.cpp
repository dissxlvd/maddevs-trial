#include "graphview.h"
#include "ui_graphview.h"

#include <QPainter>
#include <QDebug>

#include "graphpoint.h"
#include <cmath>

GraphView::GraphView(QWidget *parent) : QWidget(parent), ui(new Ui::GraphView) {
    ui->setupUi(this);
}

GraphView::~GraphView() {
    delete ui;
}

void GraphView::recPoint(QPointF point){
    if(this->points.empty()){
        this->points.push_back(point);
    } else {
        this->points.clear();
        this->points.push_back(point);
    }
    // this->points.push_back(point);
    update();
}

void GraphView::recPoints(std::vector<QPointF> recievedPoints){
    this->points.clear();

    foreach(QPointF rpoint, recievedPoints){
        this->points.push_back(rpoint);
    }

    generateGraphEdges(this->points);
    update();
}

void GraphView::generateGraphEdges(std::vector<QPointF> points){
    this->paths.clear();
    this->holyPaths.clear();
    this->holyPoints.clear();

    // Paths point to point, total of 100; do not include in final
    for(int i = 0; i < points.size() - 1; ++i){
        this->paths.push_back(std::make_pair(points[i], points[i + 1]));
    }

    // Paths from each point j to each other point k, total of 9900; include in final
    int totalPathsCount = 0;

    for(int j = 0; j < points.size(); ++j){
        GraphPoint gp(points[j]);
        gp.neighbourPaths.clear();
        for(int k = 0; k < points.size(); ++k){
            GraphPoint dp(points[k]);

            if(gp.getThisPoint() == dp.getThisPoint()){
                continue;
            } else {
                gp.availablePoints.push_back(dp);
                totalPathsCount += 1;
            }
        }
        // qDebug() << "Availible points to travel from point" << gp.getThisPoint() << ":" << gp.availablePoints.size();
        for(int k = 0; k < gp.availablePoints.size(); ++k){
            double dist = std::sqrt(
                std::pow((gp.getThisPoint().x() - gp.availablePoints[k].getThisPoint().x()), 2) +
                std::pow((gp.getThisPoint().y() - gp.availablePoints[k].getThisPoint().y()), 2)
                );

            gp.availablePaths.push_back(std::make_pair(std::make_pair(gp.getThisPoint(), gp.availablePoints[k]), dist));
        }

        // check all paths (delete later)
        if(j == 0){
            qDebug() << "ALL paths";
            for(int test = 0; test < gp.availablePaths.size(); ++test){
                qDebug() << "Path" << test + 1 <<
                    gp.availablePaths[test].first.first.getThisPoint() <<
                    gp.availablePaths[test].first.second.getThisPoint() <<
                    "Distance:" << gp.availablePaths[test].second;
            }
        }

        gp.sortByDistance(gp.availablePaths, 0, gp.availablePaths.size() - 1);

        int lowShelf = 2;
        int hiShelf = 6;

        int n = hiShelf - lowShelf + 1;
        int maxPaths = rand() % n;

        if(maxPaths < 0){
            maxPaths = -maxPaths;
        }

        maxPaths = lowShelf + maxPaths; // Normal
        // maxPaths = 1; // Debug

        for(int neighbourPath = 0; neighbourPath < maxPaths; ++neighbourPath){
            gp.neighbourPaths.push_back(gp.availablePaths[neighbourPath]);
            gp.neighbourPoints[neighbourPath] = &gp.neighbourPaths[neighbourPath].first.second;
        }

        // check sorted paths (delete later)
        if(j == 0){
            qDebug() << "Closest paths";
            for(int test = 0; test < gp.neighbourPaths.size(); ++test){
                qDebug() << "Path" << test + 1 <<
                    gp.neighbourPaths[test].first.first.getThisPoint() <<
                    gp.neighbourPaths[test].first.second.getThisPoint() <<
                    "Distance:" << gp.neighbourPaths[test].second;
            }
        }

        this->holyPoints.push_back(gp);
        emit changeStatus((static_cast<double>(j + 1) / points.size()) * 100);
    }

    foreach (GraphPoint holyPoint, holyPoints) {
        for(int holyCount = 0; holyCount < holyPoint.neighbourPaths.size(); ++holyCount){
            this->holyPaths.push_back(
                QLineF(holyPoint.neighbourPaths[holyCount].first.first.getThisPoint(),
                       holyPoint.neighbourPaths[holyCount].first.second.getThisPoint())
                );
        }
    }

    qDebug() << this->paths.size();
    qDebug() << this->holyPaths.size();
    qDebug() << this->points.size();
    qDebug() << this->holyPoints.size();

    // qDebug() << "Total paths:" << totalPathsCount;

    this->pathsGenerated = true;
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing); // Turns on antialiasing

    int graphPadding = 10; // set padding from all sides
    int viewWidth = this->width();
    int viewHeight = this->height();

    // Working area fill (Layer -1)
    painter.fillRect(
        graphPadding, // x position relative to container widget
        graphPadding, // y position relative to container widget
        viewWidth-2*graphPadding, // width
        viewHeight-2*graphPadding, // height
        Qt::black // fill (see documentation for details)
        );

    QPointF boundingCircleCenter(viewWidth/2, viewHeight/2); // = new QPointF(viewWidth/2, viewHeight/2);
    // Main circle = x^2 + y^2 = r^2
    int radius;
    const double screenMultiplier = 0.005;
    double rMultiplier = 90 * screenMultiplier; // set in percent of space being taken (0 - 100)
    if (width() > height()){
        radius = height();
    } else {
        radius = width();
    }
    // Bounding circle rendering (Layer 0)
    painter.setPen(QPen(QColor(180, 180, 180), 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(boundingCircleCenter, radius * rMultiplier, radius * rMultiplier);

    // Path rendering (Layer 1)
    painter.setPen(QPen(QColor(127, 127, 127, 255), 2, Qt::SolidLine, Qt::RoundCap));
    if(this->pathsGenerated == true){
        // qDebug() << "trying to draw paths";
        for(int i = 0; i < holyPaths.size(); ++i){
            // qDebug() << "Current path: " << this->paths[i].first << this->paths[i].second;
            // QLineF line(
            //     this->paths[i].first.x() * radius * rMultiplier + viewWidth/2,
            //     this->paths[i].first.y() * radius * rMultiplier + viewHeight/2,
            //     this->paths[i].second.x() * radius * rMultiplier + viewWidth/2,
            //     this->paths[i].second.y() * radius * rMultiplier + viewHeight/2
            //     );
            QLineF notSoHolyLine(
                this->holyPaths[i].x1() * radius * rMultiplier + viewWidth/2,
                this->holyPaths[i].y1() * radius * rMultiplier + viewHeight/2,
                this->holyPaths[i].x2() * radius * rMultiplier + viewWidth/2,
                this->holyPaths[i].y2() * radius * rMultiplier + viewHeight/2
                );
            painter.drawLine(notSoHolyLine);
        }
    }

    // Points rendering (Layer 2)
    painter.setPen(QPen(QColor(222, 222, 222), 6, Qt::SolidLine, Qt::RoundCap));
    foreach (QPointF point, this->points) {
        painter.drawPoint((point.x()) * radius * rMultiplier + viewWidth/2, (point.y()) * radius * rMultiplier + viewHeight/2);
    }
    // this->graph;
}
