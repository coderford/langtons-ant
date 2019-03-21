#include "renderarea.h"
#include <map>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    mBrushColor = QColor::fromRgb(0, 255, 255);
    mPenColor = QColor::fromRgb(255, 0, 0);

    speed = 1;
    antx = 400;
    anty = 300;
    xIncrement = 0;
    yIncrement = 1;

    img = new QImage(800, 600, QImage::Format_RGB888);
    img->fill(QColor::fromRgb(255, 255, 255));

    imgPainter = new QPainter(img);
    imgPainter->setRenderHint(QPainter::Antialiasing, true);
    imgPainter->setBrush(mBrushColor); // fill color
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    for(int i = 0; i < speed; i++) {
        imgPainter->setPen(oneStep());
        imgPainter->drawPoint(antx, anty);
    }

    QPainter actualPainter(this);
    actualPainter.drawImage(0, 0, *img);
}

QColor RenderArea::oneStep()
{
    QColor whiteColor = QColor::fromRgb(255, 255, 255);
    QColor redColor = QColor::fromRgb(255, 0, 0);
    QColor greenColor = QColor::fromRgb(0, 255, 0);
    QColor blueColor = QColor::fromRgb(0, 0, 255);

    goForward();
    if(antx < 0 || antx >= 800 || anty < 0 || anty >= 600) {
        antx -= xIncrement;
        anty -= yIncrement;
        return whiteColor;
    }
    if(img->pixelColor(antx, anty) == whiteColor) {
        turnRight();
        return redColor;
    }
    if(img->pixelColor(antx, anty) == redColor) {
        turnLeft();
        return greenColor;
    }
    if(img->pixelColor(antx, anty) == greenColor) {
        turnLeft();
        return blueColor;
    }
    if(img->pixelColor(antx, anty) == blueColor) {
        turnRight();
        return whiteColor;
    }
    return whiteColor;
}

QSize RenderArea::sizeHint() const
{
    return QSize(800, 600);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(800, 600);
}

QColor RenderArea::getBrushColor() const
{
    return this->mBrushColor;
}

void RenderArea::setBrushColor(QColor newColor)
{
    this->mBrushColor = newColor;
}

QColor RenderArea::getPenColor() const
{
    return this->mPenColor;
}

void RenderArea::setPenColor(QColor newColor)
{
    this->mPenColor = newColor;
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
    antx += xIncrement;
    anty += yIncrement;
}

void RenderArea::setSpeed(int speed)
{
    this->speed = speed;
}
