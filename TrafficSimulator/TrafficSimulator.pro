QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    car.cpp \
    game.cpp \
    grass.cpp \
    main.cpp \
    mainwindow.cpp \
    mapitem.cpp \
    scenemenager.cpp \
    street.cpp \
    view.cpp

HEADERS += \
    button.h \
    car.h \
    game.h \
    grass.h \
    mainwindow.h \
    mapitem.h \
    scenemenager.h \
    street.h \
    view.h

FORMS +=

DEFINES +=
    GAME_WIDTH
    GAME_HEIGHT

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Maps.qrc \
    images.qrc
