#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>
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
    void setSpeed(int speed);

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor mPenColor;
    QColor mBrushColor;
    int speed;
    int antx;
    int anty;
    int xIncrement;
    int yIncrement;
    QPainter *imgPainter;
    QImage *img;

    void turnLeft();
    void turnRight();
    void goForward();
    QColor oneStep();
};

#endif // RENDERAREA_H
