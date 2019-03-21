#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRgb>
#include <QMap>
#include <QPair>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    bool oneStep();		// move the ant one step forward, update color, and turn the ant

    static const int minWidth = 650;		// minimum width and height of render area
    static const int minHeight = 650;

    QMap<QRgb, QPair<char, QRgb> > moveTable;
    // ^ using QRgb because QColor is not hashable.

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    int antX;				// current x position of ant
    int antY;				// current y position of ant

    int xIncrement;			// these two specify the direction in which the ant is moving
    int yIncrement;

    QImage *img;			// off-screen image representation of screen for decoupled updating an redrawing
    QPainter *imgPainter;   // a painter for the above QImage

    void turnLeft();
    void turnRight();
    void goForward();		// move ant one block forward
};

#endif // RENDERAREA_H
