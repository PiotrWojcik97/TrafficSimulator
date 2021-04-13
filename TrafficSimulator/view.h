#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QtWidgets>
#include <QtMath>
#include <QTimer>
#include <QDebug>
#include <QList>

#include "car.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *) override;
#endif

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(QList<Car *> *_carlist, QWidget *parent = nullptr);
    void SetTimer(QTimer *_spawnCarTimer);

    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void toggleAntialiasing();
    void togglePause();
    void resetCars();
    void rotateLeft();
    void rotateRight();
    void SetCarSpawningRate();

private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label3;
    QToolButton *antialiasButton;
    QToolButton *resetButton;
    QToolButton *pauseButton;
    QToolButton *resetCarButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
    QSlider *carSpawnRateSlider;
    QTimer *spawnCarTimer;
    QList<Car *> *carlist;
};

#endif // VIEW_H
