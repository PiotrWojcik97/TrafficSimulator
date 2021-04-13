#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFile>
#include <QVector>
#include <QList>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

#include "car.h"
#include "mapitem.h"
#include "view.h"
#include "street.h"
#include "grass.h"
#include "trafficlight.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void SpawnCar();

private:
    void setupMatrix();
    void populateScene();
    void calculatePath(QList<char> *path, QPointF _sPoint, QPointF _ePoint);
    void SetUpTrafficLights();
    QVector<QPointF> spawningPoints;
    QList<Car*> carList;
    QList<TrafficLight*> trafficSignsList;
    QGraphicsScene *scene;
    //QList<QGraphicsItem> streets;
    bool checkNearestStreet(char _forbiddenDirection,QList<char> *path, QPointF _sPoint, QPointF _ePoint);

};

#endif // MAINWINDOW_H
