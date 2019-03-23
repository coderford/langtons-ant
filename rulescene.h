#ifndef RULESCENE_H
#define RULESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class RuleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit RuleScene(QObject *parent = nullptr);
    ~RuleScene();

    void construct(const QMap<QRgb, QPair<char, QRgb> > &moveTable, QRgb startColor);
    void addDownArrow(int x, int y0, int y1, int width = 10);

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int colorRectW = 40, colorRectH = 30;	// these values are used by constructRulesScene
    int colorRectGap = 10;

    QPolygon makeDirIndicator(int x, int y, int w, int h, char dir);
};

#endif // MOVEMENTRULESSCENE_H
