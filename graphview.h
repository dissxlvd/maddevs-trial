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

    void recStartPosition(int startPosition);
    void recEndPosition(int endPosition);

    void tryToFindPathSlot();
    //std::vector<GraphPoint> helper(GraphPoint newPos, GraphPoint prev);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphView *ui;

    bool pathsGenerated = false;
    bool finalPathReady = false;

    int startPosition = 0;
    int endPosition = 1;

    std::vector<QPointF> points;
    std::vector<std::pair<QPointF, QPointF>> paths;

    std::vector<GraphPoint> holyPoints;
    std::vector<QLineF> holyPaths;

    std::vector<std::vector<GraphPoint>> abomination;
    std::vector<QPointF> finalPath;

signals:
    void changeStatus(int value);
    void showLegend(bool pathsGenerated);
};

#endif // GRAPHVIEW_H
