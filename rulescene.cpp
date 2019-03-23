#include "rulescene.h"
#include <QDebug>
#include <QMap>

RuleScene::RuleScene(QObject *parent) : QGraphicsScene(parent)
{
}

RuleScene::~RuleScene()
{
}

void RuleScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        QPointF p = event->scenePos();
        qDebug() << "Clicked at: " << p.x() << p.y();
    }
    QGraphicsScene::mousePressEvent(event);
}


void RuleScene::addDownArrow(int x, int y0, int y1, int width)
{
    this->addLine(x, y0, x, y1, QPen(Qt::black));
    this->addLine(x - width/2, y1 - width/2, x, y1, QPen(Qt::black));
    this->addLine(x + width/2, y1 - width/2, x, y1, QPen(Qt::black));
}

QPolygon RuleScene::makeDirIndicator(int x, int y, int w, int h, char dir)
{
    int margin = 10;
    QPolygon arrow_triangle;
    if(dir == 'l') {
        arrow_triangle.append(QPoint(x + w/2 + margin/2, y + margin));
        arrow_triangle.append(QPoint(x + w/2 - margin/2, y + h/2));
        arrow_triangle.append(QPoint(x + w/2 + margin/2, y + h - margin));
    }
    else if(dir == 'r') {
        arrow_triangle.append(QPoint(x + w/2 - margin/2, y + margin));
        arrow_triangle.append(QPoint(x + w/2 + margin/2, y + h/2));
        arrow_triangle.append(QPoint(x + w/2 - margin/2, y + h - margin));
    }
    else qDebug() << "[makeArrowTriangle] Unknown direction!";
    return arrow_triangle;
}

void RuleScene::construct(const QMap<QRgb, QPair<char, QRgb> > &moveTable, QRgb startColor)
{
    int startx = 0, starty = 0;
    int x = startx, y = starty;
    int w = colorRectW, h = colorRectH;
    int gap = colorRectGap;
    char currDir = 'n'; 		// n means don't know yet

    QRgb currColor = startColor;

    while(true) {
        addRect(x, y, w, h, QPen(Qt::black), QBrush(QColor::fromRgba(currColor)));
        if(currDir != 'n')
            addPolygon(makeDirIndicator(x, y, w, h, currDir),
                                          QPen(QColor::fromRgb(80, 80, 80)), QBrush(Qt::black));

        currDir = moveTable[currColor].first;
        currColor = moveTable[currColor].second;

        if(currColor == startColor) break;

        addDownArrow(x + w/2, y + h, y + h + gap);
        y += gap + h;
    }

    addLine(x + w/2, y + h, x + w/2, y + h + gap, QPen(Qt::black));
    addPolygon(makeDirIndicator(startx, starty, w, h, currDir),
                                  QPen(Qt::black), QBrush(Qt::black));

    // adding lines like this is really tedious! these are for the loop
    addLine(x + w/2, y + h + gap, x + 3*w/2, y + h + gap, QPen(Qt::black));
    addLine(x + 3*w/2, y + h + gap, startx + 3*w/2, starty - gap, QPen(Qt::black));
    addLine(startx + 3*w/2, starty - gap, startx + w/2, starty - gap, QPen(Qt::black));
    addDownArrow(startx + w/2, starty - gap, starty);
}
