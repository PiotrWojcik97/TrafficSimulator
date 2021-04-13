#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), scene(new QGraphicsScene(this))
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    populateScene();


    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(SpawnCar()));
    timer->start(1000);    //1 car per 1s

    View *view = new View(&carList);
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
    QList<char> path;
    calculatePath(&path,sPoint,ePoint);

    Car *item = new Car(sPoint.rx(),sPoint.ry(),&path);
    carList.push_back(item);
    item->GetCarList(&carList);
    item->SetTrafficLightsList(&trafficSignsList);
    item->setPos(sPoint);
    scene->addItem(item);
}

void MainWindow::populateScene()
{
    QFile mapFile(":/maps/map2.txt");           //File
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
                if(line[i] == 'S' || line[i] == 'T')              //If in file is S, paint steet
                {
                    Street *item = new Street(rowX, columnY);
                    item->setPos(QPointF(rowX*100, columnY*100));
                    scene->addItem(item);
                    if(line[i] == 'T')
                    {
                        TrafficLight *trafficLight = new TrafficLight(rowX, columnY);
                        trafficSignsList.push_back(trafficLight);
                        trafficLight->setPos(QPointF(rowX*100, columnY*100));
                        item->SetTrafficLight(trafficLight);
                    }
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
    SetUpTrafficLights();
    mapSize[1] = columnY;

}

bool MainWindow::checkNearestStreet(char _forbiddenDirection,QList<char> *path, QPointF _sPoint, QPointF _ePoint)
{
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
                if(checkNearestStreet('L', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('R');
                }
            }
            if(_sPoint.x() - 100 == item->x() && _sPoint.y() == item->y() )
            {
                if(checkNearestStreet('R', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('L');
                }
            }
            if(_sPoint.x() == item->x() && _sPoint.y() + 100 == item->y() )
            {
                if(checkNearestStreet('U', path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('D');
                }
            }
            if(_sPoint.x() == item->x() && _sPoint.y() - 100 == item->y() )
            {
                if(checkNearestStreet('D',path, QPointF(item->x(),item->y()),_ePoint))
                {
                   path->push_front('U');
                }
            }
        }
    }
}

void MainWindow::SetUpTrafficLights()
{
    for(auto it : trafficSignsList)
    {
        foreach (QGraphicsItem* item, scene->items())
        {
           if (item->type() == Street::Type)
           {
               if( it->GetX()*100 + 100 == item->x() && it->GetY()*100  == item->y() )
               {
                    it->SetLight('R');
               }
               if( it->GetX()*100 - 100 == item->x() && it->GetY()*100  == item->y() )
               {
                    it->SetLight('L');
               }
               if( it->GetX()*100 == item->x() && it->GetY()*100 + 100 == item->y() )
               {
                    it->SetLight('D');
               }
               if( it->GetX()*100 == item->x() && it->GetY()*100 - 100 == item->y() )
               {
                    it->SetLight('U');
               }
            }
        }
        scene->addItem(it);
    }
}
