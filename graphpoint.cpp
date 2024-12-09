#include "graphpoint.h"

GraphPoint::GraphPoint(QPointF pointptr) {
    this->xPos = pointptr.x();
    this->yPos = pointptr.y();

    this->thisPoint = pointptr;
}

GraphPoint::~GraphPoint() {}

QPointF GraphPoint::getThisPoint(){
    return this->thisPoint;
}

/// QuickSort implementation
int GraphPoint::partition(std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> availablePaths, int startIndex, int endIndex){
    double pivot = this->availablePaths[endIndex].second;
    int i = startIndex - 1;

    for(int j = startIndex; j <= endIndex - 1; ++j){
        if(this->availablePaths[j].second < pivot){
            ++i;
            std::pair<std::pair<GraphPoint, GraphPoint>, double> temp = this->availablePaths[i];
            this->availablePaths[i] = this->availablePaths[j];
            this->availablePaths[j] = temp;
        }
    }
    ++i;
    std::pair<std::pair<GraphPoint, GraphPoint>, double> temp = this->availablePaths[i];
    this->availablePaths[i] = this->availablePaths[endIndex];
    this->availablePaths[endIndex] = temp;

    return i;
}

void GraphPoint::sortByDistance(std::vector<std::pair<std::pair<GraphPoint, GraphPoint>, double>> availablePaths, int startIndex, int endIndex){
    // this->availablePaths = availablePaths;
    if(endIndex <= startIndex){
        return;
    }

    int pivot = partition(this->availablePaths, startIndex, endIndex);
    sortByDistance(this->availablePaths, startIndex, pivot - 1);
    sortByDistance(this->availablePaths, pivot + 1, endIndex);
}
/// QuickSort implementation
