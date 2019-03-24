#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    antX = minWidth/2;		// ant starts off in the middle of render-area
    antY = minHeight/2;
    xIncrement = 0;			// ant's initial direction is up
    yIncrement = -1;

    // initializing the render buffer and the painter for it
    backgroundColor = QColor::fromRgb(255, 255, 255, 255).rgba();
    img = new QImage(minWidth, minHeight, QImage::Format_ARGB32);
    img->fill(backgroundColor);

    imgPainter = new QPainter(img);
    imgPainter->setRenderHint(QPainter::Antialiasing, true);

    // move table initialization

    /* some interesting rules:
     * rlrlrl llllll
     * llrrlr rrrrrr
     * llrrll rrllrr
     * rrll
     * lrrl
     * rrrlr
     */
    QRgb whiteRgb = QColor::fromRgb(255, 255, 255, 255).rgba();
    QRgb redRgb = QColor::fromRgb(255, 0, 0, 255).rgba();
    QRgb greenRgb = QColor::fromRgb(0, 255, 0, 255).rgba();
    QRgb blueRgb = QColor::fromRgb(0, 0, 255, 255).rgba();
    QRgb yellowRgb = QColor::fromRgb(255, 255, 0, 255).rgba();
    QRgb pinkRgb = QColor::fromRgb(255, 0, 255, 255).rgba();
    QRgb greyRgb = QColor::fromRgb(30, 30, 30, 255).rgba();
    QRgb brownRgb = QColor::fromRgb(100, 20, 20, 255).rgba();
    QRgb darkGreenRgb = QColor::fromRgb(30, 30, 150, 255).rgba();
    QRgb cyanRgb = QColor::fromRgb(0, 255, 255, 255).rgba();
    QRgb darkYellowRgb = QColor::fromRgb(150, 150, 0, 255).rgba();
    QRgb darkPinkRgb = QColor::fromRgb(150, 20, 150, 255).rgba();

    moveTable[darkPinkRgb] = QPair<char, QRgb>('r', whiteRgb);
    moveTable[whiteRgb] = QPair<char, QRgb>('l', redRgb);
    moveTable[redRgb] = QPair<char, QRgb>('r', greenRgb);
    moveTable[greenRgb] = QPair<char, QRgb>('l', blueRgb);
    moveTable[blueRgb] = QPair<char, QRgb>('r', yellowRgb);
    moveTable[yellowRgb] = QPair<char, QRgb>('l', pinkRgb);
    moveTable[pinkRgb] = QPair<char, QRgb>('l', greyRgb);
    moveTable[greyRgb] = QPair<char, QRgb>('l', brownRgb);
    moveTable[brownRgb] = QPair<char, QRgb>('l', darkGreenRgb);
    moveTable[darkGreenRgb] = QPair<char, QRgb>('l', cyanRgb);
    moveTable[cyanRgb] = QPair<char, QRgb>('l', darkYellowRgb);
    moveTable[darkYellowRgb] = QPair<char, QRgb>('l', darkPinkRgb);

    constructColorIndex();
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

QRgb RenderArea::getBackgroundColor() const
{
    return backgroundColor;
}

void RenderArea::setBackgroundColor(QColor color)
{
    backgroundColor = color.rgba();
}

void RenderArea::reset()
{
    antX = minWidth/2;		// ant starts off in the middle of render-area
    antY = minHeight/2;
    xIncrement = 0;			// ant's initial direction is up
    yIncrement = -1;

    // initializing the render buffer and the painter for it
    img->fill(backgroundColor);
}

void RenderArea::constructColorIndex()
{
    colorIndex.clear();
    colorIndex.push_back(backgroundColor);

    QRgb currColor = moveTable[backgroundColor].second;
    while(currColor != backgroundColor) {
        colorIndex.push_back(currColor);
        currColor = moveTable[currColor].second;
    }
}

void RenderArea::flipDirAtIndex(int index)
{
    QRgb color;
    if(index > 0)
        color = colorIndex[index-1];
    else
        color = colorIndex[colorIndex.size()-1];

    if(moveTable[color].first == 'l')
        moveTable[color].first = 'r';
    else
        moveTable[color].first = 'l';
}

void RenderArea::setNewColorAtIndex(int index, QRgb newColor)
{
    QRgb oldColor;
    oldColor = colorIndex[index];

    QPair<char, QRgb> save = moveTable[oldColor];
    moveTable.remove(oldColor);
    moveTable[newColor] = save;
    colorIndex[index] = newColor;

    if(index == 0) moveTable[colorIndex[colorIndex.size()-1]].second = newColor;
    else moveTable[colorIndex[index-1]].second = newColor;
}
