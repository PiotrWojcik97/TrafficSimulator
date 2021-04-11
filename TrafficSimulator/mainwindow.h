#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QFile>
#include <QVector>
#include <QList>

#include "car.h"

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
    QVector<QPointF> spawningPoints;
    QList<Car*> carList;
    QGraphicsScene *scene;
    //QList<QGraphicsItem> streets;
    bool checkNearestStreet(char _forbiddenDirection,QList<char> *path, QPointF _sPoint, QPointF _ePoint);

};

#endif // MAINWINDOW_H
