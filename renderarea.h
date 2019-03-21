#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <vector>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QColor getPenColor() const;
    void setPenColor(QColor newColor);
    QColor getBrushColor() const;
    void setBrushColor(QColor newColor);

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor mPenColor;
    QColor mBrushColor;
    int antx;
    int anty;
    int xIncrement;
    int yIncrement;
    int steps;
    std::vector<std::vector<QColor> > colorMap;

    void turnLeft();
    void turnRight();
    void goForward();
};

#endif // RENDERAREA_H
