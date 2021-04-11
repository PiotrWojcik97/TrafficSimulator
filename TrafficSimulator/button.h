#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QObject>
#include <QtDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QApplication>
//#include <QWidget>

class Button : public QObject, public QGraphicsPixmapItem
{
   // Q_OBJECT
public:
    Button(short _buttonID, int PosX, int PosY, QPixmap *_pixmap , QGraphicsScene *_mainScenePtr,QGraphicsItem *parent = nullptr);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override;
private:
    QPixmap *pix_image;
    QGraphicsRectItem rect;
    QGraphicsScene *mainScenePtr;
    unsigned short buttonID;
};
#endif // BUTTON_H
