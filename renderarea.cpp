#include "renderarea.h"
#include <map>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    antX = minWidth/2;		// ant starts off in the middle of render-area
    antY = minHeight/2;
    xIncrement = 0;			// ant's initial direction is down
    yIncrement = 1;

    img = new QImage(minWidth, minHeight, QImage::Format_RGB888);
    img->fill(QColor::fromRgb(255, 255, 255));

    imgPainter = new QPainter(img);
    imgPainter->setRenderHint(QPainter::Antialiasing, true);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter actualPainter(this);
    actualPainter.drawImage(0, 0, *img);
}

bool RenderArea::oneStep()
{
    QColor whiteColor = QColor::fromRgb(255, 255, 255);
    QColor redColor = QColor::fromRgb(255, 0, 0);
    QColor greenColor = QColor::fromRgb(0, 255, 0);
    QColor blueColor = QColor::fromRgb(0, 0, 255);
    QColor nextColor;

    goForward();
    if(antX < 0 || antX >= minWidth || antY < 0 || antY >= minHeight) {
        antX -= xIncrement;
        antY -= yIncrement;
        return false;
    }
    if(img->pixelColor(antX, antY) == whiteColor) {
        turnRight();
        nextColor = redColor;
    }
    else if(img->pixelColor(antX, antY) == redColor) {
        turnLeft();
        nextColor = greenColor;
    }
    else if(img->pixelColor(antX, antY) == greenColor) {
        turnLeft();
        nextColor = blueColor;
    }
    else if(img->pixelColor(antX, antY) == blueColor) {
        turnRight();
        nextColor = whiteColor;
    }

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

void RenderArea::turnLeft()
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

void RenderArea::turnRight()
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
