#include "grass.h"

Grass::Grass(int x, int y)
{
    this->setFlag(ItemStacksBehindParent);
    this->x = x;
    this->y = y;
}


void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(QColor(0, 255, 0, 127));  // R,G,B,transparent
    painter->drawRect(5, 5, 90, 90);
}
