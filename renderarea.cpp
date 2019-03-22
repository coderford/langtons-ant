#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    antX = minWidth/2;		// ant starts off in the middle of render-area
    antY = minHeight/2;
    xIncrement = 0;			// ant's initial direction is up
    yIncrement = -1;

    // initializing the render buffer and the painter for it
    img = new QImage(minWidth, minHeight, QImage::Format_ARGB32);
    img->fill(Qt::white);

    imgPainter = new QPainter(img);
    imgPainter->setRenderHint(QPainter::Antialiasing, true);

    // move table initialization
    QRgb whiteRgb = QColor::fromRgb(255, 255, 255, 255).rgba();
    QRgb redRgb = QColor::fromRgb(255, 0, 0, 255).rgba();
    QRgb greenRgb = QColor::fromRgb(0, 255, 0, 255).rgba();
    QRgb blueRgb = QColor::fromRgb(0, 0, 255, 255).rgba();
    QRgb yellowRgb = QColor::fromRgb(255, 255, 0, 255).rgba();

    moveTable[whiteRgb] = QPair<char, QRgb>('r', redRgb);
    moveTable[redRgb] = QPair<char, QRgb>('r', greenRgb);
    moveTable[greenRgb] = QPair<char, QRgb>('l', blueRgb);
    moveTable[blueRgb] = QPair<char, QRgb>('r', yellowRgb);
    moveTable[yellowRgb] = QPair<char, QRgb>('r', whiteRgb);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter actualPainter(this);
    actualPainter.drawImage(0, 0, *img);
}

bool RenderArea::oneStep()
{
    goForward();
    if(antX < 0 || antX >= minWidth || antY < 0 || antY >= minHeight) {
        antX -= xIncrement;
        antY -= yIncrement;
        return false;
    }

    QRgb currRgb = img->pixel(antX, antY);
    if(moveTable[currRgb].first == 'l') turnLeft();
    if(moveTable[currRgb].first == 'r') turnRight();
    QColor nextColor = QColor::fromRgba(moveTable[currRgb].second);

    imgPainter->setPen(nextColor);
    imgPainter->drawPoint(antX, antY);
    return true;
}

QSize RenderArea::sizeHint() const
{
    return QSize(minWidth, minHeight);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(minWidth, minHeight);
}

void RenderArea::turnRight()
{
    if(xIncrement == 0 && yIncrement == 1) {
       xIncrement = -1;
       yIncrement = 0;
    }
    else if(xIncrement == 1 && yIncrement == 0) {
       xIncrement = 0;
       yIncrement = 1;
    }
    else if(xIncrement == 0 && yIncrement == -1) {
       xIncrement = 1;
       yIncrement = 0;
    }
    else if(xIncrement == -1 && yIncrement == 0) {
       xIncrement = 0;
       yIncrement = -1;
    }
}

void RenderArea::turnLeft()
{
    if(xIncrement == 0 && yIncrement == 1) {
       xIncrement = 1;
       yIncrement = 0;
    }
    else if(xIncrement == 1 && yIncrement == 0) {
       xIncrement = 0;
       yIncrement = -1;
    }
    else if(xIncrement == 0 && yIncrement == -1) {
       xIncrement = -1;
       yIncrement = 0;
    }
    else if(xIncrement == -1 && yIncrement == 0) {
       xIncrement = 0;
       yIncrement = 1;
    }
}

void RenderArea::goForward()
{
    antX += xIncrement;
    antY += yIncrement;
}
