#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QtWidgets>
#include <QtMath>
#include <QTimer>
#include <QDebug>

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
    explicit View(QWidget *parent = nullptr);
    void SetTimer(QTimer *_spawnCarTimer);

    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void toggleAntialiasing();
    void rotateLeft();
    void rotateRight();
    void SetCarSpawningRate();

private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QToolButton *antialiasButton;
    QToolButton *resetButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
    QSlider *carSpawnRateSlider;
    QTimer *spawnCarTimer;
};

#endif // VIEW_H
