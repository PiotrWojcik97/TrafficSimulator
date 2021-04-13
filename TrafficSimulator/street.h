#ifndef STREET_H
#define STREET_H

#include "mapitem.h"
#include "trafficlight.h"

QT_BEGIN_NAMESPACE
class MapItem;
QT_END_NAMESPACE

class Street : public MapItem
{
public:
    Street(int x, int y);
    enum { Type = UserType + 1 };
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int type() const override;
    void SetTrafficLight(TrafficLight *_trafficLight);
};

#endif // STREET_H
