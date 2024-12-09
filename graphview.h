#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include "graphpoint.h"

namespace Ui {
class GraphView;
}

class GraphView : public QWidget {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

    void generateGraphEdges(std::vector<QPointF> points);

public slots:
    void recPoint(QPointF point);
    void recPoints(std::vector<QPointF> recievedPoints);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphView *ui;

    bool pathsGenerated = false;
    std::vector<QPointF> points;
    std::vector<std::pair<QPointF, QPointF>> paths;

    std::vector<GraphPoint> holyPoints;
    std::vector<QLineF> holyPaths;

signals:
    void changeStatus(int value);
};

#endif // GRAPHVIEW_H
