#include "game.h"

Game::Game()
{
    view.setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    view.setScene(&mainScene);
    mainScene.setSceneRect(0,0,GAME_WIDTH,GAME_HEIGHT);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Traffic simulator"));
    view.setBackgroundBrush(QPixmap(":/images/images/background.jpg"));
}

void Game::Show()
{

    //button_start->setPos(250,200);
    //mainScene.addItem(button_start);
    //button_options->setPos(250,300);
    //mainScene.addItem(button_options);
    view.show();
}
