#include "street.h"

Street::Street(int x, int y)
{
    this->x = x;
    this->y = y;
}


void Street::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(QColor(0, 0, 0, 127));  // R,G,B,transparent
    painter->drawRect(5, 5, 90, 90);
}

int Street::type() const
{
    //Enable the use of qgraphicsitem_cast with this item.
    return Type;
}
