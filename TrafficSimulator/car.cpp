#include "car.h"

Car::Car(int x, int y,QList<char> *_path)
{
    this->x = x;
    this->y = y;
    this->setFlag(ItemStacksBehindParent);
    this->setFlag(ItemIsSelectable);
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
    timer->start(timerspeed);    //60 FPS 17 was before
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

void Car::SetTrafficLightsList(QList<TrafficLight *> *_trafficLightList)
{
    this->trafficLightList = _trafficLightList;
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

bool Car::CheckIfOtherCarHasRedLight()
{
    return hasRedLight;
}

void Car::PauseTimer()
{
    timer->stop();
}

void Car::ResumeTimer()
{
    timer->start(timerspeed);
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
    if(checkIfCarHasRedLight())
        return false;

    for (auto it: *carlist)
    {
        if(it != this)
        {
            QLineF lineToCar(QPointF(0, 0), mapFromItem(it, 0, 0));

            if(lineToCar.length() < 160)
            {
                char dir = it->GetCarDir();
                bool otherLeftTurnSingal = it->GetleftTurnSignal();
                bool otherRightTurnSingal = it->GetRightTurnSignal();   //not used, var for future precedence sings.
                bool otherCarHasRedLight = it->CheckIfOtherCarHasRedLight();

                //Right hand rule scenario
                if(HandleRightHandRule(otherCarHasRedLight,otherLeftTurnSingal,dir,it->x,it->y))
                    return false;

                //Car is in front a car scenario
                if(HandleCarInFrontOfTheCar(distanceToJunction, otherCarHasRedLight,otherLeftTurnSingal,dir,it->x,it->y))
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

bool Car::checkIfCarHasRedLight()
{
    for (auto it: *trafficLightList)
    {
        hasRedLight = false;
        QLineF lineToLights(QPointF(0, 0), mapFromItem(it, 0, 0));
        if(lineToLights.length() > 100 && lineToLights.length() < 110)
        {
            //If car has already passed the traffic light.
            if(imagePosition == 'R' && this->x > it->GetX()*100)
                return false;
            if(imagePosition == 'L' && this->x < it->GetX()*100)
                return false;
            if(imagePosition == 'D' && this->y > it->GetY()*100)
                return false;
            if(imagePosition == 'U' && this->y < it->GetY()*100)
                return false;

            //If car did not passed the traffic light,
            //update car parameter hasRedLight and return it.
            if(imagePosition == 'R')
                it->GetLight('L',hasRedLight);
            else if(imagePosition == 'L')
                it->GetLight('R',hasRedLight);
            else if(imagePosition == 'D')
                it->GetLight('U',hasRedLight);
            else if(imagePosition == 'U')
                it->GetLight('D',hasRedLight);
        }
    }
    return hasRedLight;
}

bool Car::HandleRightHandRule(bool otherCarHasRedLight, bool _otherLeftTurnSingal, char _dir, int _x, int _y)
{
    //True - Car should stop
    //False - Car should drive

    if(imagePosition == 'R' && _dir == 'U')                 //If cars are positioned in the right hand scenario.
        if(!otherCarHasRedLight)                            //If the other car does not have red light.
            if( !_otherLeftTurnSingal && !leftTurnSignal )  //If both of them are NOT turning left (usually it happens without collision).
                if( this->x < _x && this->y < _y )          //If cars have not already passed each other.
                    return true;
    if(imagePosition == 'U' && _dir == 'L')
        if(!otherCarHasRedLight)
            if( !_otherLeftTurnSingal && !leftTurnSignal )
                if( this->x < _x && this->y > _y )
                    return true;
    if(imagePosition == 'L' && _dir == 'D')
        if(!otherCarHasRedLight)
            if( !_otherLeftTurnSingal && !leftTurnSignal )
                if( this->x > _x && this->y > _y )
                    return true;
    if(imagePosition == 'D' && _dir == 'R')
        if(!otherCarHasRedLight)
            if( !_otherLeftTurnSingal && !leftTurnSignal )
                if( this->x > _x && this->y < _y )
                    return true;

    return false;
}

bool Car::HandleCarInFrontOfTheCar(int _distanceToJunction,bool otherCarHasRedLight, bool _otherLeftTurnSingal, char _dir, int _x, int _y)
{
    //True - Car should stop
    //False - Car should drive
    if(imagePosition == 'R' && _dir == 'L')                 //If car is in fron of the other car.
        if(!otherCarHasRedLight)                            //If the other car does not have red light.
            if(leftTurnSignal && !_otherLeftTurnSingal)     //If both of them are not turning left.
                if(this->x < _x )                           //If cars have not already passed each other.
                    if( _distanceToJunction < 5)            //if car reached the junction.
                        return true;
    if(imagePosition == 'L' && _dir == 'R')
        if(!otherCarHasRedLight)
            if(leftTurnSignal && !_otherLeftTurnSingal)
                if(this->x > _x )
                    if( _distanceToJunction < 5)
                        return true;
    if(imagePosition == 'D' && _dir == 'U')
        if(!otherCarHasRedLight)
            if(leftTurnSignal && !_otherLeftTurnSingal)
                if(this->y < _y )
                    if( _distanceToJunction < 5)
                        return true;
    if(imagePosition == 'U' && _dir == 'D')
        if(!otherCarHasRedLight)
            if(leftTurnSignal && !_otherLeftTurnSingal)
                if(this->y > _y )
                    if( _distanceToJunction < 5)
                        return true;

    return false;
}
