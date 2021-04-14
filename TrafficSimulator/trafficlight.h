#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QGraphicsScene>

#include "mapitem.h"

QT_BEGIN_NAMESPACE
class MapItem;
class Light;
QT_END_NAMESPACE

struct LightStr
{
    bool isPresent = false;
    bool isRed = true;
};
/**
 * @brief The TrafficLight class
 * Handles Trafic lights behaviour.
 */
class TrafficLight : public QObject, public MapItem
{
    Q_OBJECT
public:
    TrafficLight(int x, int y);
    ~TrafficLight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int GetX();
    int GetY();
    void SetLight(char c);
    void GetLight(char c, bool &isRed);

public slots:
    void Blink();
private:
    QTimer *timer;
    bool changedir = false;
    LightStr u_light, d_light, r_light, l_light;
};

#endif // TRAFFICLIGHT_H
