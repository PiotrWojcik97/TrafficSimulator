#ifndef GRASS_H
#define GRASS_H


#include "mapitem.h"

QT_BEGIN_NAMESPACE
class MapItem;
QT_END_NAMESPACE

class Grass : public MapItem
{
public:
    Grass(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

#endif // GRASS_H
