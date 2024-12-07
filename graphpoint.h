#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

class GraphPoint {
public:
    GraphPoint();
    ~GraphPoint();

private:
    float xPos;
    float yPos;

    GraphPoint* neighbourPoints[6];
};

#endif // GRAPHPOINT_H
