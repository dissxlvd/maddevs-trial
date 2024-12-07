#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>

namespace Ui {
class GraphView;
}

class GraphView : public QWidget {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

public slots:
    void recievePoint(QPointF point);
    void recieveGraph(std::vector<QPointF> recievedPoints);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphView *ui;
    std::vector<QPointF> points;
};

#endif // GRAPHVIEW_H
