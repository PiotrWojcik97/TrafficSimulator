#include "mapitem.h"

QRectF MapItem::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

QPainterPath MapItem::shape() const
{
    QPainterPath path;
    path.addRect(10, 10, 80, 80);
    return path;
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(QColor(255, 0, 0, 127));  // R,G,B,transparent
    painter->drawRect(5, 5, 90, 90);
}
int MapItem::type() const
{
    //Enable the use of qgraphicsitem_cast with this item.
    return Type;
}

