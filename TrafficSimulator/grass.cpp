#include "grass.h"

Grass::Grass(int x, int y)
{
    this->x = x;
    this->y = y;

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}


void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    // Specify semi-transparent red
    painter->setBrush(QColor(0, 255, 0, 127));  // R,G,B,transparent
    painter->drawRect(5, 5, 90, 90);

}
