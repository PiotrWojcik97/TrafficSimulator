#include "trafficlight.h"

TrafficLight::TrafficLight(int x, int y)
{
    this->x = x;
    this->y = y;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Blink()));
    timer->start(2000);    //Blink every 2s
}

TrafficLight::~TrafficLight()
{
    timer->stop();
    delete timer;
}

void TrafficLight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    if(u_light.isPresent)
    {
        if(u_light.isRed)
        {
            painter->setBrush(QColor(200, 0, 0, 255));
            painter->drawEllipse(0,0,25,25);
        }
        else
        {
            painter->setBrush(QColor(0, 200, 0, 255));
            painter->drawEllipse(0,0,25,25);
        }
    }
    if(d_light.isPresent)
    {
        if(d_light.isRed)
        {
            painter->setBrush(QColor(200, 0, 0, 255));
            painter->drawEllipse(75,75,25,25);
        }
        else
        {
            painter->setBrush(QColor(0, 200, 0, 255));
            painter->drawEllipse(75,75,25,25);
        }
    }
    if(r_light.isPresent)
    {
        if(r_light.isRed)
        {
            painter->setBrush(QColor(200, 0, 0, 255));
            painter->drawEllipse(0,75,25,25);
        }
        else
        {
            painter->setBrush(QColor(0, 200, 0, 255));
            painter->drawEllipse(0,75,25,25);
        }
    }
    if(l_light.isPresent)
    {
        if(l_light.isRed)
        {
            painter->setBrush(QColor(200, 0, 0, 255));
            painter->drawEllipse(75,0,25,25);
        }
        else
        {
            painter->setBrush(QColor(0, 200, 0, 255));
            painter->drawEllipse(75,0,25,25);
        }
    }
}

int TrafficLight::GetX()
{
    return x;
}

int TrafficLight::GetY()
{
    return y;
}

void TrafficLight::SetLight(char c)
{
    if(c == 'U')
        u_light.isPresent = true;
    if(c == 'D')
        d_light.isPresent = true;
    if(c == 'L')
        l_light.isPresent = true;
    if(c == 'R')
        r_light.isPresent = true;
}

void TrafficLight::GetLight(char c, bool &isRed)
{
    if(c == 'U')
    {
        if(u_light.isRed)
            isRed = true;
        else
            isRed = false;
    }
    if(c == 'D')
    {
        if(d_light.isRed)
            isRed = true;
        else
            isRed = false;
    }
    if(c == 'R')
    {
        if(r_light.isRed)
            isRed = true;
        else
            isRed = false;
    }
    if(c == 'L')
    {
        if(l_light.isRed)
            isRed = true;
        else
            isRed = false;
    }
}

void TrafficLight::Blink()
{
    if(changedir)
    {
        u_light.isRed = true;
        d_light.isRed = true;
        l_light.isRed = false;
        r_light.isRed = false;
        changedir = false;
    }
    else
    {
        u_light.isRed = false;
        d_light.isRed = false;
        l_light.isRed = true;
        r_light.isRed = true;
        changedir = true;
    }
    this->update(0,0,0,0); //force QT to update colors
}
