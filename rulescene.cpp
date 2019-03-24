#include "rulescene.h"
#include <QDebug>
#include <QMap>
#include <QGraphicsItem>

RuleScene::RuleScene(QObject *parent) : QGraphicsScene(parent)
{
}

bool RuleScene::isPointInRect(int px, int py, int rx, int ry, int w, int h)
{
    if(px < rx || px > rx + w) return false;
    if(py < ry || py > ry + h) return false;
    return true;
}

void RuleScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        QPointF clickPos = event->scenePos();
        int x = clickPos.x(), y = clickPos.y();

        if(x >= 0 && x <= colorRectW) {
            /* click was in the right horizontal range */
            int rectIndex = y / (colorRectH + colorRectGap);

            if(y % (colorRectH + colorRectGap) <= colorRectH) {
                /* click was inside a color rectangle and not in gap */

                int rx = startX + colorRectW/2 - dirW/2;
                int ry = startY + rectIndex * (colorRectH + colorRectGap) + colorRectH/2 - dirH/2;
                if(isPointInRect(x, y, rx, ry, dirH, dirW)) {
                    emit dirArrowClicked(rectIndex);
                }
                else emit colorRectClicked(rectIndex);
            }
        }
    }
}


void RuleScene::addDownArrow(int x, int y0, int y1, int width)
{
    this->addLine(x, y0, x, y1, QPen(Qt::black));
    this->addLine(x - width/2, y1 - width/2, x, y1, QPen(Qt::black));
    this->addLine(x + width/2, y1 - width/2, x, y1, QPen(Qt::black));
}

QPolygon RuleScene::makeDirIndicator(char dir, int x, int y, int w, int h)
{
    QPolygon arrow_triangle;
    if(dir == 'l') {
        arrow_triangle.append(QPoint(x + w,  y));
        arrow_triangle.append(QPoint(x, y + h/2));
        arrow_triangle.append(QPoint(x + w,  y + h));
    }
    else if(dir == 'r') {
        arrow_triangle.append(QPoint(x, y));
        arrow_triangle.append(QPoint(x + w, y + h/2));
        arrow_triangle.append(QPoint(x, y + h));
    }
    else qDebug() << "[makeArrowTriangle] Unknown direction!";
    return arrow_triangle;
}

void RuleScene::construct(const QMap<QRgb, QPair<char, QRgb> > &moveTable, QRgb startColor)
{
    int x = startX, y = startY;
    int w = colorRectW, h = colorRectH;
    int gap = colorRectGap;
    char currDir = 'n'; 		// n means don't know yet

    QRgb currColor = startColor;

    while(true) {
        addRect(x, y, w, h, QPen(Qt::black), QBrush(QColor::fromRgba(currColor)));
        if(currDir != 'n')
            addPolygon(makeDirIndicator(currDir, x + w/2 - dirW/2, y + h/2 - dirH/2, dirW, dirH),
                                          QPen(QColor::fromRgb(80, 80, 80)), QBrush(Qt::black));

        currDir = moveTable[currColor].first;
        currColor = moveTable[currColor].second;

        if(currColor == startColor) break;

        addDownArrow(x + w/2, y + h, y + h + gap);
        y += gap + h;
    }

    addLine(x + w/2, y + h, x + w/2, y + h + gap, QPen(Qt::black));
    addPolygon(makeDirIndicator(currDir, startX + w/2 - dirW/2, startY + h/2 - dirH/2, dirW, dirH),
                                  QPen(Qt::black), QBrush(Qt::black));

    // adding lines like this is really tedious! these are for the loop
    addLine(x + w/2, y + h + gap, x + 3*w/2, y + h + gap, QPen(Qt::black));
    addLine(x + 3*w/2, y + h + gap, startX + 3*w/2, startY - gap, QPen(Qt::black));
    addLine(startX + 3*w/2, startY - gap, startX + w/2, startY - gap, QPen(Qt::black));
    addDownArrow(startX + w/2, startY - gap, startY);
}
