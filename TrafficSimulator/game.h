#ifndef GAME_H
#define GAME_H

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtDebug>
#include <map>
#include "scenemenager.h"

class Game
{
public:
    Game();
    void Show();
protected:
    QGraphicsScene mainScene;
private:
    QGraphicsView view;
    SceneMenager scenemenager = SceneMenager(&mainScene);
};

#endif // GAME_H
