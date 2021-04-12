#ifndef CAR_H
#define CAR_H

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

#include "mapitem.h"

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
    enum { Type = UserType + 2 };
    ~Car();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int type() const override
       {
           // Enable the use of qgraphicsitem_cast with this item.
           return Type;
       }
    void GetCarList(QList<Car*> *_carlist);
    char GetCarDir();
    bool GetleftTurnSignal();
    bool GetRightTurnSignal();

public slots:
    void drive();
protected:
    //void timerEvent(QTimerEvent *event) override;
private:
    QTimer *timer;
    QList<CarPath> path;
    char imagePosition;
    bool CheckIfCarShouldDrive(int distanceToJunction);
    QList<Car*> *carlist;
    bool leftTurnSignal = false;
    bool rightTurnSignal = false;
};


#endif // CAR_H
