#ifndef SCENEMENAGER_H
#define SCENEMENAGER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <list>
#include <map>
#include <QObject>
#include <QtDebug>
#include <QPushButton>

class SceneMenager : public QMainWindow
{
    Q_OBJECT
public:
    explicit SceneMenager(QGraphicsScene *_mainScenePtr,QWidget *parent = nullptr);
    ~SceneMenager() {};
    void HandleScene(int sceneId);
protected:
    //bool eventFilter(QObject *obj, QEvent *event) override;
private slots:
    void handleButton();
private:
    QVector <QPointF> spawningPoints;
    std::map<std::string,QPixmap> images;
    QGraphicsScene *mainScenePtr;
    QPushButton *m_button;
    void BuildMainScene();
    void BuildOptionsScene();
    void BuildGameScene();
    void CleanCurrentScene();
    void BuildSimulatorScene();
};

/*class KeyPressEater : public QObject
{
    Q_OBJECT
public:
    KeyPressEater();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
   // if (event->type() == QEvent::KeyPress) {
     //   QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press");//, keyEvent->key());
        return true;
    //} //else {
        // standard event processing
      //  return false/QObject::eventFilter(obj, event);
    //}
}

KeyPressEater::KeyPressEater()
{

}*/


#endif // SCENEMENAGER_H
