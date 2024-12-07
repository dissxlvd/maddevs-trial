#include "graphview.h"
#include "ui_graphview.h"

#include <QPainter>
#include <QDebug>

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

    for(int i = 0; i < points.size() - 1; ++i){
        this->paths.push_back(std::make_pair(points[i], points[i + 1]));
    }

    this->pathsGenerated = true;
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int graphPadding = 10; // set padding from all sides
    int viewWidth = this->width();
    int viewHeight = this->height();

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
    const float screenMultiplier = 0.005;
    float rMultiplier = 90 * screenMultiplier; // set in percent of space being taken (0 - 100)
    if (width() > height()){
        radius = height();
    } else {
        radius = width();
    }

    painter.setPen(QPen(QColor(180, 180, 180), 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(boundingCircleCenter, radius * rMultiplier, radius * rMultiplier);

    painter.setPen(QPen(QColor(222, 222, 222), 6, Qt::SolidLine, Qt::RoundCap));

    foreach (QPointF point, this->points) {
        painter.drawPoint((point.x()) * radius * rMultiplier + viewWidth/2, (point.y()) * radius * rMultiplier + viewHeight/2);
    }

    painter.setPen(QPen(QColor(0, 0, 255, 100), 1, Qt::SolidLine, Qt::RoundCap));
    if(this->pathsGenerated == true){
        qDebug() << "trying to draw paths";
        for(int i = 0; i < paths.size(); ++i){
            qDebug() << "Current path: " << this->paths[i].first << this->paths[i].second;
            QLineF line(
                this->paths[i].first.x() * radius * rMultiplier + viewWidth/2,
                this->paths[i].first.y() * radius * rMultiplier + viewHeight/2,
                this->paths[i].second.x() * radius * rMultiplier + viewWidth/2,
                this->paths[i].second.y() * radius * rMultiplier + viewHeight/2
                );
            painter.drawLine(line);
        }
    }
    // this->graph;
}
