#include "scenemenager.h"

SceneMenager::SceneMenager(QGraphicsScene *_mainScenePtr,QWidget *parent) : QMainWindow(parent)
{
    images["start"] = QPixmap(":/images/images/button_start.png");
    images["options"] = QPixmap(":/images/images/button_options.png");
    mainScenePtr = _mainScenePtr;

    m_button = new QPushButton("My Button", this);
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(m_button, &QPushButton::released, this, &SceneMenager::handleButton);
    mainScenePtr->addWidget(m_button);

    BuildMainScene();

}

void SceneMenager::handleButton()
{
  // change the text
  m_button->setText("Example");
  // resize button
  m_button->resize(100,100);
}

//bool SceneMenager::eventFilter(QObject *obj, QEvent *event)
//{
   // if (event->type() == QEvent::KeyPress) {
     //   QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        qDebug("Ate key press");//, keyEvent->key());
 //       return true;
    //} //else {
        // standard event processing
      //  return false/QObject::eventFilter(obj, event);
    //}
//}


void SceneMenager::BuildMainScene()
{
   //Button button1 = Button(0,250,200,&images["start"],mainScenePtr);
   //startButton = new Button(0,250,200,&images["start"],mainScenePtr);
   //startButton->installEventFilter(this);
   //buttons.push_front(new Button(0,250,200,&images["start"],mainScenePtr));
   //buttons.push_front(new Button(1,250,300,&images["options"],mainScenePtr));
   // buttons.insert(Button(1,250,300,&images["options"],mainScenePtr));

   //CleanCurrentScene();
   //Button *button_start = new Button(0,250,200,&images["start"],mainScenePtr);
   //Button *button_options = new Button(1,250,300,&images["options"],mainScenePtr);
}

void SceneMenager::CleanCurrentScene()
{
    //for(auto it : buttons)
    //{
    //    delete it;
    //}
}

void SceneMenager::BuildSimulatorScene()
{

}
