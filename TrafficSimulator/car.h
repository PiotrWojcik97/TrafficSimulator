#ifndef CAR_H
#define CAR_H

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

#include "mapitem.h"
#include "trafficlight.h"

QT_BEGIN_NAMESPACE
class MapItem;
QT_END_NAMESPACE

struct CarPath
{
    char direction;
    int distance;
};

class Car : public QObject, public MapItem
{
    Q_OBJECT
public:
    Car(int x, int y,QList<char> *_path);
    ~Car();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void GetCarList(QList<Car*> *_carlist);
    void SetTrafficLightsList(QList<TrafficLight*> *_trafficLightList);
    char GetCarDir();
    bool GetleftTurnSignal();
    bool GetRightTurnSignal();
    bool CheckIfOtherCarHasRedLight();
    void PauseTimer();
    void ResumeTimer();

public slots:
    void drive();

private:
    QTimer *timer;
    QList<CarPath> path;
    QList<Car*> *carlist;
    QList<TrafficLight*> *trafficLightList;
    char imagePosition;
    bool CheckIfCarShouldDrive(int distanceToJunction);
    bool leftTurnSignal = false;
    bool rightTurnSignal = false;
    bool hasRedLight = false;
    bool checkIfCarHasRedLight();
    bool HandleRightHandRule(bool otherCarHasRedLight, bool _otherLeftTurnSingal, char _dir, int _x, int _y);
    bool HandleCarInFrontOfTheCar(int _distanceToJunction, bool otherCarHasRedLight, bool _otherLeftTurnSingal, char _dir, int _x, int _y);
    int timerspeed = 8;
};


#endif // CAR_H
