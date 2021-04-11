#include "button.h"

Button::Button(short _buttonID, int PosX, int PosY, QPixmap *_pixmap, QGraphicsScene *_mainScenePtr, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    pix_image = _pixmap;
    setPixmap(*pix_image);
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlags(QGraphicsItem::ItemIsSelectable);
    mainScenePtr = _mainScenePtr;
    buttonID = _buttonID;
    setPos(PosX,PosY);
    mainScenePtr->addItem(this);
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *e) {
    //qDebug()<<"Information! "<< "Mouse release Detected!"<<this->pos().x();
    //mainScenePtr->clear();
    //QMessageBox::information(NULL, "Information!", "Mouse release Detected!");
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    //graphicsscene.addRect(pixmap.rect(), new QPen(), new QBrush(new QColor(255, 255, 255, 128)));
    //qDebug()<<"Information! "<< "Mouse hover enter Detected!";
    rect.setRect(this->pos().x()-1,this->pos().y()-1,pix_image->width()+1,pix_image->height()+1);
    mainScenePtr->addItem(&rect);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    //qDebug()<<"Information! "<< "Mouse hover leave Detected!";
    rect.setRect(this->pos().x()-1,this->pos().y()-1,pix_image->width()+1,pix_image->height()+1);
    mainScenePtr->removeItem(&rect);
};
