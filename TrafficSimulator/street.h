#ifndef STREET_H
#define STREET_H

#include "mapitem.h"
#include "trafficlight.h"

QT_BEGIN_NAMESPACE
class MapItem;
QT_END_NAMESPACE
/**
 * @brief The Street class
 * Streets are present on a map.
 * Have special Type to gain possibility to
 * distinguish between others map items.
 */
class Street : public MapItem
{
public:
    Street(int x, int y);
    enum { Type = UserType + 1 };
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int type() const override;
};

#endif // STREET_H
