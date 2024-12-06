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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphView *ui;
};

#endif // GRAPHVIEW_H
