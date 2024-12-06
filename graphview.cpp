#include "graphview.h"
#include "ui_graphview.h"

#include "graph.h"
#include "point.h"

#include <QPainter>
#include <QDebug>

GraphView::GraphView(QWidget *parent) : QWidget(parent), ui(new Ui::GraphView) {
    ui->setupUi(this);
}

GraphView::~GraphView() {
    delete ui;
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // QPen pen(QColor(255, 255, 255), 1, Qt::SolidLine, Qt::RoundCap); -> white 1px round solid line

    int graphPadding = 10; // set padding from all sides
    int viewWidth = this->width();
    int viewHeight = this->height();

    // qDebug() << this->width() << " " << this->height();
    painter.fillRect(
        graphPadding, // x position relative to container widget
        graphPadding, // y position relative to container widget
        viewWidth-2*graphPadding, // width
        viewHeight-2*graphPadding, // height
        Qt::black // fill (see documentation for details)
        );

    // Main circle = x^2 + y^2 = r^2
    QPointF *boundingCircleCenter = new QPointF(viewWidth/2, viewHeight/2);

    int radius;
    const float screenMultiplier = 0.005;
    float rMultiplier = 90 * screenMultiplier; // set in percent of space being taken (0 - 100)
    if (width() > height()){
        radius = height();
    } else {
        radius = width();
    }

    painter.setPen(QPen(QColor(255, 255, 255), 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(*boundingCircleCenter, radius * rMultiplier, radius * rMultiplier);

    painter.setPen(QPen(QColor(0, 255, 0), 4, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(QPoint(viewWidth/2, viewHeight/2));
}
