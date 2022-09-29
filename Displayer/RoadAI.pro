QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += mqtt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkpoint.cpp \
    circle.cpp \
    controlleradapter.cpp \
    controllermanager.cpp \
    banana.cpp \
    checkpoint.cpp \
    circle.cpp \
    gameproperties.cpp \
    main.cpp \
    mainwindow.cpp \
    maptranslator.cpp \
    mqttdialog.cpp \
    options.cpp \
    rectangle.cpp

HEADERS += \
    options.cpp \
    player.cpp \
    rectangle.cpp \
    rocket.cpp

HEADERS += \
    banana.h \
    checkpoint.h \
    circle.h \
    circuitelement.h \
    controlleradapter.h \
    controllermanager.h \
    displayview.h \
    gameproperties.h \
    gamescreen.h \
    keyboardcontroller.h \
    mainwindow.h \
    mapinfo.h \
    maptranslator.h \
    mqttdialog.h \
    options.h \
    optionslayer.h \
    rectangle.h \
    registerlayer.h \
    startscreenlayer.h \
    vehicleproperties.h

    gameproperties.h \
    gamescreen.h \
    mainwindow.h \
    mapinfo.h \
    maptranslator.h \
    options.h \
    optionslayer.h \
    player.h \
    rectangle.h \
    rocket.h \
    startscreenlayer.h \
    vehicleproperties.h

resources.files = \
    options.txt
resources.prefix = /

RESOURCES += \
    banana.qrc \
    banana2.qrc \
    bike.qrc \
    car.qrc \
    rocket.qrc \
    truck.qrc




FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    banana.png \
    ressources/banana.gif
