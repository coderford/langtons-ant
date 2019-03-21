#include "renderarea.h"
#include <QTimer>
#include <QDebug>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    mBrushColor = QColor::fromRgb(0, 255, 255);
    mPenColor = QColor::fromRgb(255, 0, 0);

    steps = 10000000;
    antx = 400;
    anty = 300;
    xIncrement = 0;
    yIncrement = 1;
    colorMap.assign(800, std::vector<QColor>(600, QColor::fromRgb(255, 255, 255)));
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QColor whiteColor = QColor::fromRgb(255, 255, 255);
    QColor redColor = QColor::fromRgb(255, 0, 0);
    QColor greenColor = QColor::fromRgb(0, 255, 0);
    QColor blueColor = QColor::fromRgb(0, 0, 255);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(mBrushColor); // fill color

    for(int i = 0; i < steps; i++) {
        goForward();
        if(antx < 0 || antx > colorMap.size() || anty < 0 || anty > colorMap.size())
            break;
        // qDebug() << "antx: " << antx << ", anty: " << anty;
        if(colorMap[antx][anty] == whiteColor) {
            colorMap[antx][anty] = redColor;
            painter.setPen(redColor);
            painter.drawPoint(antx, anty);
            turnLeft();
        }
        else if(colorMap[antx][anty] == redColor) {
            QColor nextColor = greenColor;
            colorMap[antx][anty] = nextColor;
            painter.setPen(nextColor);
            painter.drawPoint(antx, anty);
            turnRight();
        }
        else if(colorMap[antx][anty] == greenColor) {
            colorMap[antx][anty] = blueColor;
            painter.setPen(blueColor);
            painter.drawPoint(antx, anty);
            turnRight();
        }
        else if(colorMap[antx][anty] == blueColor) {
            colorMap[antx][anty] = whiteColor;
            painter.setPen(whiteColor);
            painter.drawPoint(antx, anty);
            turnLeft();
        }
    }
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

void RenderArea::turnLeft() {
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

void RenderArea::turnRight() {
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

void RenderArea::goForward() {
    antx += xIncrement;
    anty += yIncrement;
}
