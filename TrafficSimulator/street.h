#ifndef STREET_H
#define STREET_H

#include "mapitem.h"

QT_BEGIN_NAMESPACE
class MapItem;
QT_END_NAMESPACE

class Street : public MapItem
{
public:
    Street(int x, int y);
    enum { Type = UserType + 1 };
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int getX();
    int getY();
    int type() const override
       {
           // Enable the use of qgraphicsitem_cast with this item.
           return Type;
       }
private:
};

#endif // STREET_H
