#include <QApplication>
#include <QGraphicsScene>
#include <car.h>
#include <QGraphicsView>
#include "game.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;
    window.show();

    return app.exec();
    //QApplication app(argc, argv);

   // MainWindow mainWindow;
    //mainWindow.show();
    //mainWindow.ShowView();
    //Game game;
    //game.Show();


    /*
    QGraphicsScene *scene = new QGraphicsScene();

    Car * car = new Car();

    car->setRect(0,0,100,100); //x,y,width,height

    scene->addItem(car);

    //make item focusable
    car->setFlag(QGraphicsItem::ItemIsFocusable);
    car->setFocus();


    QGraphicsView * view = new QGraphicsView(scene);
    //view->setScene(scene);

    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);
    view->show();

    car->setPos(view->width()/2,view->height()/2);*/
    //return app.exec();
}
