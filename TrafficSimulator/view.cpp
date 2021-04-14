#include "view.h"

#if QT_CONFIG(wheelevent)
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->angleDelta().y() > 0)
            view->zoomIn(6);
        else
            view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
#endif

View::View(QList<Car *> *_carlist,QWidget *parent)
    : QFrame(parent)
{
    this->carlist = _carlist;

    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomSlider);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);
    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);

    // Rotate slider layout
    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftIcon);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("Reset View"));
    resetButton->setEnabled(false);

    // Label layout(TOP one)
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label3 = new QLabel(tr("Car Spawn Rate"));

    pauseButton = new QToolButton;
    pauseButton->setText(tr("Pause"));
    pauseButton->setCheckable(true);
    pauseButton->setChecked(false);
    resetCarButton = new QToolButton;
    resetCarButton->setText(tr("Reset Cars"));
    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);
    carSpawnRateSlider = new QSlider;
    carSpawnRateSlider->setOrientation(Qt::Horizontal);
    carSpawnRateSlider->setMinimum(0);
    carSpawnRateSlider->setMaximum(100);
    carSpawnRateSlider->setValue(10);
    carSpawnRateSlider->setTickPosition(QSlider::TicksBelow);
    dropDownList = new QComboBox;
    dropDownList->addItem("Map 1");
    dropDownList->addItem("Map 2");
    dropDownList->addItem("Map 3");


    QHBoxLayout *carSpawnRateSliderLayoutTOP = new QHBoxLayout;
    carSpawnRateSliderLayoutTOP->addStretch();
    carSpawnRateSliderLayoutTOP->addWidget(label3);
    carSpawnRateSliderLayoutTOP->addStretch();

    QVBoxLayout *carSpawnRateSliderLayout = new QVBoxLayout;
    carSpawnRateSliderLayout->addLayout(carSpawnRateSliderLayoutTOP);
    carSpawnRateSliderLayout->addWidget(carSpawnRateSlider);


    QButtonGroup *pointerModeGroup = new QButtonGroup(this);
    pointerModeGroup->setExclusive(true);

    labelLayout->addLayout(carSpawnRateSliderLayout);
    labelLayout->addWidget(resetCarButton);
    labelLayout->addWidget(pauseButton);
    labelLayout->addWidget(dropDownList);
    labelLayout->addStretch();
    labelLayout->addWidget(antialiasButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addLayout(rotateSliderLayout, 2, 0);
    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(resetButton, &QAbstractButton::clicked, this, &View::resetView);
    connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(rotateSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(carSpawnRateSlider, &QAbstractSlider::valueChanged, this, &View::SetCarSpawningRate);
    connect(graphicsView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            this, &View::setResetButtonEnabled);
    connect(graphicsView->horizontalScrollBar(), &QAbstractSlider::valueChanged,
            this, &View::setResetButtonEnabled);
    connect(antialiasButton, &QAbstractButton::toggled, this, &View::toggleAntialiasing);
    connect(resetCarButton, &QAbstractButton::clicked, this, &View::resetCars);
    connect(pauseButton, &QAbstractButton::toggled, this, &View::togglePause);
    connect(rotateLeftIcon, &QAbstractButton::clicked, this, &View::rotateLeft);
    connect(rotateRightIcon, &QAbstractButton::clicked, this, &View::rotateRight);
    connect(dropDownList, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ HandleDropDownList(index); });
    setupMatrix();
}

void View::SetTimer(QTimer *_spawnCarTimer)
{
    this->spawnCarTimer = _spawnCarTimer;
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QTransform matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateSlider->value());

    graphicsView->setTransform(matrix);
    setResetButtonEnabled();
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::togglePause()
{
    if(pauseButton->isChecked())
    {
        spawnCarTimer->stop();
        for( auto it : *carlist)
            it->PauseTimer();
    }
    else
    {
        spawnCarTimer->start(100*carSpawnRateSlider->value());
        for( auto it : *carlist)
            it->ResumeTimer();
    }
}

void View::resetCars()
{
    for( auto it : *carlist)
        delete it;
    carlist->clear();
}

void View::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}

void View::SetCarSpawningRate()
{
    spawnCarTimer->start(100*carSpawnRateSlider->value());
}

void View::HandleDropDownList(int index)
{
    emit MapIndexChanged(index);
}
