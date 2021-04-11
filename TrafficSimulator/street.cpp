#include "street.h"

Street::Street(int x, int y)
{
    this->x = x;
    this->y = y;

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}


void Street::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    // Specify semi-transparent red
    painter->setBrush(QColor(0, 0, 0, 127));  // R,G,B,transparent
    painter->drawRect(5, 5, 90, 90);

}

int Street::getX()
{
    return this->x;
}

int Street::getY()
{
    return this->y;
}


