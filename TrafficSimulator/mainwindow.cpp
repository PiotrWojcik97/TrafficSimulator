#include "mainwindow.h"
#include "mapitem.h"
#include "view.h"
#include "street.h"
#include "grass.h"

#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this))
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    populateScene();


    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(SpawnCar()));
    timer->start(1000);    //1 car per 1s

    View *view = new View("Simulator");
    view->view()->setScene(scene);
    view->SetTimer(timer);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Traffic simulator"));
}

void MainWindow::SpawnCar()
{
    int startingPoint = QRandomGenerator::global()->generate() % spawningPoints.size();
    int endingPoint = 0;
    do
    {
        endingPoint = QRandomGenerator::global()->generate() % spawningPoints.size();
    }
    while (endingPoint == startingPoint);

    QPointF sPoint = spawningPoints[startingPoint];
    QPointF ePoint = spawningPoints[endingPoint];
   // qDebug() << "Start from: " << sPoint << " End on: " << ePoint;
    QList<char> path;
    calculatePath(&path,sPoint,ePoint);

    Car *item = new Car(sPoint.rx(),sPoint.ry(),&path);
   carList.push_back(item);
    qDebug()<<"list size: " << carList.size();
    item->GetCarList(&carList);
    item->setPos(sPoint);
    scene->addItem(item);
}

void MainWindow::populateScene()
{
    QFile mapFile(":/maps/map1.txt");           //File
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&mapFile);
    QString line = in.readLine();
    int columnY = 0;
    int mapSize[2] = {0,0};
    while (!line.isNull())
    {
        for(int i=0, rowX=0; i<line.length();i++)
        {
            if(line[i] != ' ')                  //If in file is space, skip it
            {
                if(line[i] == 'S')              //If in file is S, paint steet
                {
                    QGraphicsItem *item = new Street(rowX, columnY);
                    item->setPos(QPointF(rowX*100, columnY*100));
                    scene->addItem(item);
                    //streets.push_back(item);
                }
                if(line[i] == 'G')              //If in file is G, paint grass
                {
                    QGraphicsItem *item = new Grass(rowX, columnY);
                    item->setPos(QPointF(rowX*100, columnY*100));
                    scene->addItem(item);
                }
                if(line[i] == 'P')              //If in file is P, spawn point
                {
                    spawningPoints.push_back(QPointF(rowX*100, columnY*100));
                }
                rowX++;
            }
            if(i+1 == line.length())
                if(mapSize[0] < rowX)
                    mapSize[0] = rowX;
        }
        line = in.readLine();
        if(!line.isNull())
            columnY++;
    }
    mapSize[1] = columnY;

    /*foreach (QGraphicsItem* item, scene->items())
    {
        if (item->type() == Street::Type)
        {
           qDebug() << "Steet list: ";
           qDebug() << QPointF(item->x(),item->y());

        }
    }*/

}

bool MainWindow::checkNearestStreet(char _forbiddenDirection,QList<char> *path, QPointF _sPoint, QPointF _ePoint)
{
    //qDebug() << "starting Point: " <<_sPoint <<" ending point: " << _ePoint;
    foreach (QGraphicsItem* item, scene->items())
    {
        if (item->type() == Street::Type)
        {
            if(_forbiddenDirection != 'R')
            {
                if(_sPoint.x() + 100 == item->x() && _sPoint.y() == item->y() )
                {
                    if(checkNearestStreet('L',path,QPointF(item->x(),item->y()),_ePoint))
                    {
                        path->push_front('R');
                        return true;
                    }
                }
            }
            if(_forbiddenDirection != 'L')
            {
                if(_sPoint.x() - 100 == item->x() && _sPoint.y() == item->y() )
                {
                    if(checkNearestStreet('R',path,QPointF(item->x(),item->y()),_ePoint))
                    {
                        path->push_front('L');
                        return true;
                    }
                }
            }
            if(_forbiddenDirection != 'U')
            {
                if(_sPoint.x() == item->x() && _sPoint.y() - 100 == item->y() )
                {
                    if(checkNearestStreet('D',path,QPointF(item->x(),item->y()),_ePoint))
                    {
                        path->push_front('U');
                        return true;
                    }
                }
            }
            if(_forbiddenDirection != 'D')
            {
                if(_sPoint.x() == item->x() && _sPoint.y() + 100 == item->y() )
                {
                    if(checkNearestStreet('U',path,QPointF(item->x(),item->y()),_ePoint))
                    {
                        path->push_front('D');
                        return true;
                    }
                }
            }
        }
    }
    if(_sPoint.x() + 100 == _ePoint.x() && _sPoint.y() == _ePoint.y() )
    {
        path->push_front('R');
        return true;
    }
    if(_sPoint.x() - 100 == _ePoint.x() && _sPoint.y() == _ePoint.y() )
    {
        path->push_front('L');
        return true;
    }
    if(_sPoint.x()== _ePoint.x() && _sPoint.y() - 100  == _ePoint.y() )
    {
        path->push_front('U');
        return true;
    }
    if(_sPoint.x()== _ePoint.x() && _sPoint.y() + 100  == _ePoint.y() )
    {
        path->push_front('D');
        return true;
    }
    return false;
}

void MainWindow::calculatePath(QList<char> *path, QPointF _sPoint, QPointF _ePoint)
{
    foreach (QGraphicsItem* item, scene->items())
    {
       if (item->type() == Street::Type)
       {
            if(_sPoint.x() + 100 == item->x() && _sPoint.y() == item->y() )
            {
               // qDebug() << "street is on the right";
                if(checkNearestStreet('L', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('R');
                }
            }
            if(_sPoint.x() - 100 == item->x() && _sPoint.y() == item->y() )
            {
                //qDebug() << "street is on the left";
                if(checkNearestStreet('R', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('L');
                }
            }
            if(_sPoint.x() == item->x() && _sPoint.y() + 100 == item->y() )
            {
                //qDebug() << "street is under";
                if(checkNearestStreet('U', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('D');
                }
            }
            if(_sPoint.x() == item->x() && _sPoint.y() - 100 == item->y() )
            {
                //qDebug() << "street is above";
                if(checkNearestStreet('D',path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('U');
                }
            }
        }
    }
    //qDebug() << *path;
   // qDebug()<< path->size();
}

/*
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent), scene(new QGraphicsScene(this))
{
    view.setFixedSize(800,800);
    view.setScene(&scene);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic simulator"));
    BuildMainScene();
    //populateScene();
}

void MainWindow::ShowView()
{
    view.show();
}

void MainWindow::handleStartButton()
{
    DestroyMainScene();
    BuildSimulatorScene();
}

void MainWindow::handleOptionsButton()
{
  // change the text
  options_button->setText("Example");
  // resize button
  options_button->resize(100,100);
}

void MainWindow::DestroyMainScene()
{
    //delete start_button;
    //delete options_button;
    scene.clear();
}

void MainWindow::BuildMainScene()
{
    // Create the button, make "this" the parent
    start_button = new QPushButton("My Button");
    // set size and location of the button
    start_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Connect button signal to appropriate slot
    connect(start_button, &QPushButton::released, this, &MainWindow::handleStartButton);
    scene.addText("HEHEHE");

    proxy = scene.addWidget(start_button);
    //proxy->setPos(300, 200);
    //scene->addWidget(start_button);
    //view.setScene(&scene);
    //view.show();

    options_button = new QPushButton("My Button", this);
    options_button->setGeometry(QRect(QPoint(100, 400), QSize(200, 50)));
    connect(options_button, &QPushButton::released, this, &MainWindow::handleOptionsButton);
    //scene.clear();
}

void MainWindow::BuildSimulatorScene()
{
    populateScene();
}

void MainWindow::populateScene()
{
    const int MAP_SIZE = 1000;
    // Populate scene
    int xx = 0;
    int nitems = 0;

    for (int i = 0; i < MAP_SIZE; i += 100) {
        ++xx;
        int yy = 0;
        for (int j = 0; j < MAP_SIZE; j += 100) {
            ++yy;
            //QColor color(image.pixel(int(image.width() * x), int(image.height() * y)));
            QGraphicsItem *item = new MapItem(xx, yy);
            item->setPos(QPointF(i, j));
            scene.addItem(item);

            ++nitems;
        }
    }
}
*/
