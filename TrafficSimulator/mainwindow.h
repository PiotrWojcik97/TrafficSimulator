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
/**
 * @brief The MainWindow class
 * Handles MainWindow of the application.
 * In this class there are implemented:
 * -spawning car feature.
 * -findpath algorithm feature.
 * -handling of scene maps.
 * -initializing of all scene objects.
 * PROCLAIMER:
 * findpath algorithm does not work with find the shorthest path,
 * also it is capable of finding end to end path. It does not work
 * with scenario when multiple paths can lead to end point.
 * It does not have any protection against doom maps.
 */
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void SpawnCar();

private:
    void setupMatrix();
    void populateScene(int mapIndex);
    void ChangeMap(int index);
    void calculatePath(QList<char> *path, QPointF _sPoint, QPointF _ePoint);
    void SetUpTrafficLights();
    void CleanCurrentScene();
    QVector<QPointF> spawningPoints;
    QList<Car*> carList;
    QList<TrafficLight*> trafficSignsList;
    QGraphicsScene *scene;
    bool checkNearestStreet(char _forbiddenDirection,QList<char> *path, QPointF _sPoint, QPointF _ePoint);

};

#endif // MAINWINDOW_H
