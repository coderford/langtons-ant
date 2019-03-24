#ifndef RULESCENE_H
#define RULESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class RuleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit RuleScene(QObject *parent = nullptr);

    void construct(const QMap<QRgb, QPair<char, QRgb> > &moveTable, QRgb startColor);
    void addDownArrow(int x, int y0, int y1, int width = 10);

signals:
    void dirArrowClicked(int index);
    void colorRectClicked(int index);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int colorRectW = 40, colorRectH = 30;	// these values are used by constructRulesScene
    int colorRectGap = 10;
    int startX = 0;
    int startY = 0;
    int dirW = 16, dirH = 16;

    QPolygon makeDirIndicator(char dir, int x, int y, int w, int h);

    bool isPointInRect(int px, int py, int rx, int ry, int w, int h);
};

#endif // MOVEMENTRULESSCENE_H
