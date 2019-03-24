#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRgb>
#include <QMap>
#include <QPair>
#include <QVector>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    bool oneStep();					// move the ant one step forward, update color, and turn the ant

    static const int minWidth = 650;			// minimum width and height of render area
    static const int minHeight = 650;

    QMap<QRgb, QPair<char, QRgb> > moveTable; 	// using QRgb as QColor is not hashable
    QVector<QRgb> colorIndex;		// a table used to index into the moveTable; index 0 is backgroundColor

    QRgb getBackgroundColor() const;
    void setBackgroundColor(QColor color);

    void flipDirAtIndex(int index);
    void setNewColorAtIndex(int index, QRgb newColor);
    void clearScreen();

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    int antX;				// current x position of ant
    int antY;				// current y position of ant

    int antXMax;			// these keep track of the bounds of the figure
    int antYMax;
    int antXMin;
    int antYMin;

    int viewPortX;
    int viewPortY;
    int viewPortW;			// what part of the image should be viewed?
    int viewPortH;

    int xIncrement;			// these two specify the direction in which the ant is moving
    int yIncrement;

    QRgb backgroundColor;	// the background color; will be the first color in movement rules
    QImage *img;			// off-screen image representation of screen for decoupled updating an redrawing
    QPainter *imgPainter;   // a painter for the above QImage

    void constructColorIndex();

    void turnLeft();
    void turnRight();
    void goForward();		// move ant one block forward

    void expandViewPort();
};

#endif // RENDERAREA_H
