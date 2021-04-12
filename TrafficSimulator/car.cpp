#include "car.h"

Car::Car(int x, int y,QList<char> *_path)
{
    this->x = x;
    this->y = y;

    QList<char> :: iterator it;
    QList<CarPath> :: iterator carIt;
    for(it = _path->begin(), carIt = path.begin(); it != _path->end(); ++it)
    {
        if(carIt == NULL)
        {
            CarPath temp;
            temp.direction = *it;
            temp.distance = 100;
            path.push_back(temp);
            carIt = path.begin();
            imagePosition = *it;
            continue;
        }

        if(*it == carIt->direction)
        {
            carIt->distance += 100;
        }
        else
        {
            CarPath temp;
            temp.direction = *it;
            temp.distance = 100;
            path.push_back(temp);
            carIt++;
        }
    }

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(drive()));
    timer->start(8);    //60 FPS 17 was before
}

Car::~Car()
{
    timer->stop();
    delete timer;

     int i=0;
     for(auto it: *carlist)
     {
         if(it == this)
             break;
         i++;
     }
     carlist->removeAt(i);
}


void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(QColor(50, 100, 255, 255));  // R,G,B,transparent
    if(imagePosition == 'L')
        painter->drawRect(5, 5, 90, 40);
    if(imagePosition == 'R')
        painter->drawRect(5, 55, 90, 40);
    if(imagePosition == 'D')
        painter->drawRect(5, 5, 40, 90);
    if(imagePosition == 'U')
        painter->drawRect(55, 5, 40, 90);

    if(leftTurnSignal)
    {
       painter->setBrush(QColor(255, 100, 10, 255));  // R,G,B,transparent
       if(imagePosition == 'L')
           painter->drawRect(10, 35, 10, 10);
       if(imagePosition == 'R')
           painter->drawRect(80, 55, 10, 10);
       if(imagePosition == 'D')
           painter->drawRect(35, 80, 10, 10);
       if(imagePosition == 'U')
           painter->drawRect(55, 10, 10, 10);
    }
    if(rightTurnSignal)
    {
       painter->setBrush(QColor(255, 100, 10, 255));  // R,G,B,transparent
       if(imagePosition == 'L')
           painter->drawRect(10, 5, 10, 10);
       if(imagePosition == 'R')
           painter->drawRect(80, 85, 10, 10);
       if(imagePosition == 'D')
           painter->drawRect(5, 80, 10, 10);
       if(imagePosition == 'U')
           painter->drawRect(85, 10, 10, 10);
    }

}

void Car::GetCarList(QList<Car *> *_carlist)
{
    this->carlist = _carlist;
}

char Car::GetCarDir()
{
    return imagePosition;
}

bool Car::GetleftTurnSignal()
{
    return leftTurnSignal;
}

bool Car::GetRightTurnSignal()
{
    return rightTurnSignal;
}

void Car::drive()
{
    if(!path.isEmpty())
    {
        QList<CarPath> :: iterator carIt = path.begin();
        if(carIt->distance < 200)
        {
            char direction = carIt->direction;
            carIt++;
            char nextCarDirection = carIt->direction;
            if( direction == 'R')
            {
                if(nextCarDirection == 'D')
                    rightTurnSignal = true;
                if(nextCarDirection == 'U')
                    leftTurnSignal = true;
            }
            if( direction == 'L')
            {
                if(nextCarDirection == 'U')
                    rightTurnSignal = true;
                if(nextCarDirection == 'D')
                    leftTurnSignal = true;
            }
            if( direction == 'D')
            {
                if(nextCarDirection == 'L')
                    rightTurnSignal = true;
                if(nextCarDirection == 'R')
                    leftTurnSignal = true;
            }
            if( direction == 'U')
            {
                if(nextCarDirection == 'R')
                    rightTurnSignal = true;
                if(nextCarDirection == 'L')
                    leftTurnSignal = true;
            }

        }
        carIt = path.begin();
        if( CheckIfCarShouldDrive(carIt->distance) )
        {
            if(imagePosition != carIt->direction)
            {
                imagePosition = carIt->direction;
            }
            if(carIt->direction == 'R')
            {
                this->setPos(QPointF(x++,y));
                carIt->distance--;
            }
            if(carIt->direction == 'L')
            {
                this->setPos(QPointF(x--,y));
                carIt->distance--;
            }
            if(carIt->direction == 'D')
            {
                this->setPos(QPointF(x,y++));
                carIt->distance--;
            }
            if(carIt->direction == 'U')
            {
                this->setPos(QPointF(x,y--));
                carIt->distance--;
            }
            if(carIt->distance <= 0)
            {
                path.removeFirst();
                rightTurnSignal = false;
                leftTurnSignal = false;
            }
        }
    }
    else
    {
        delete this;
    }
}

bool Car::CheckIfCarShouldDrive(int distanceToJunction)
{
    for (auto it: *carlist)
    {
        if(it != this)
        {
            QLineF lineToCar(QPointF(0, 0), mapFromItem(it, 0, 0));

            if(lineToCar.length() < 160)
            {
                char dir = it->GetCarDir();
                bool otherLeftTurnSingal = it->GetleftTurnSignal();
                bool otherRightTurnSingal = it->GetRightTurnSignal();
                const int offset1 = 50;
                const int offset2 = 20;
                //Right hand rule scenario

                    if(imagePosition == 'R' && dir == 'U')
                        if( !otherLeftTurnSingal && !leftTurnSignal )
                            if(this->y > it->y + offset2 )
                                if(this->x + offset1 < it->x )
                                   return false;
                    if(imagePosition == 'U' && dir == 'L')
                        if( !otherLeftTurnSingal && !leftTurnSignal )
                            if(this->x < it->x + offset2 )
                                if(this->y + offset1 > it->y )
                                    return false;
                    if(imagePosition == 'L' && dir == 'D')
                        if( !otherLeftTurnSingal && !leftTurnSignal )
                            if(this->y < it->y + offset2 )
                               if(this->x + offset1 > it->x)
                                  return false;
                    if(imagePosition == 'D' && dir == 'R')
                        if( !otherLeftTurnSingal && !leftTurnSignal )
                            if(this->y + offset1 < it->y )
                                if(this->x > it->x + offset2 )
                                    return false;

                    //Car is in front a car scenario
                    if(imagePosition == 'R' && dir == 'L')
                        if(leftTurnSignal && !otherLeftTurnSingal)
                            if(this->x + 30 > it->x )
                                return false;
                    if(imagePosition == 'L' && dir == 'R')
                        if(leftTurnSignal && !otherLeftTurnSingal)
                           if(this->x + 30 < it->x )
                                return false;
                    if(imagePosition == 'D' && dir == 'U')
                        if(leftTurnSignal && !otherLeftTurnSingal)
                            if(this->y + 30 > it->y )
                                return false;
                    if(imagePosition == 'U' && dir == 'D')
                        if(leftTurnSignal && !otherLeftTurnSingal)
                            if(this->y + 30 < it->y )
                                return false;

                if(lineToCar.length() < 110)
                {

                    //Car behind a car scenario
                    if( dir == 'R' && dir == imagePosition)
                        if(it->x > this->x)
                            return false;
                    if( dir == 'L' && dir == imagePosition)
                        if(it->x < this->x)
                            return false;
                    if( dir == 'D' && dir == imagePosition)
                        if(it->y > this->y)
                            return false;
                    if( dir == 'U' && dir == imagePosition)
                        if(it->y < this->y)
                            return false;

                }
            }
        }
    }

    return true;
}
