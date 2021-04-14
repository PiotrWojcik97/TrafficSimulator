#ifndef MAPITEM_H
#define MAPITEM_H

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
/**
 * @brief The MapItem class
 * Abstract class for certain map items.
 */
class MapItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    enum { Type = UserType + 2 };
    int type() const override;
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int x;
    int y;
private:
};

#endif // MAPITEM_H
