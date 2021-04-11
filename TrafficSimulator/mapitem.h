#ifndef MAPITEM_H
#define MAPITEM_H

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class MapItem : public QGraphicsItem
{
public:
    //MapItem(int x, int y);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int x;
    int y;
private:
};

#endif // MAPITEM_H
