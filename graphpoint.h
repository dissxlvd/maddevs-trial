#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

#include <QPointF>

class GraphPoint {
public:
    GraphPoint(QPointF pointptr);
    ~GraphPoint();

    // returns self (QPointF type)
    QPointF getThisPoint();

    // Stores all points to which travel is possible (no restrictions)
    std::vector<GraphPoint> availablePoints;
    // Stores all paths on which travel is possible (no restrictions)
    std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> availablePaths;

    // Stores all points closest to this (max 6)
    GraphPoint* neighbourPoints[6];
    // Stores all paths with lowest distance to this (max 6)
    std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> neighbourPaths;

    bool isVisited(); // returns if this point has been visited or not
    void setVisited(); // sets this point as 'visited'
    void resetVisited(); // sets this point as 'unvisited' (resets to false)

    int partition(std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> availablePaths, int startIndex, int endIndex);
    void sortByDistance(std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> availablePaths, int startIndex, int endIndex);

private:
    double xPos;
    double yPos;

    bool visited = false;

    QPointF thisPoint;
};

#endif // GRAPHPOINT_H
