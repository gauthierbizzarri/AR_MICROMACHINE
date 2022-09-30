QT       += core gui mqtt gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkpoint.cpp \
    circle.cpp \
    connectionlayer.cpp \
    controlleradapter.cpp \
    controllermanager.cpp \
    banana.cpp \
    bomb.cpp \
    gamepadcontroller.cpp \
    gameproperties.cpp \
    gamescreen.cpp \
    keyboardcontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    mapinfo.cpp \
    maptranslator.cpp \
    mqttdialog.cpp \
    options.cpp \
    optionslayer.cpp \
    player.cpp\
    registerlayer.cpp \
    power.cpp \
    rocket.cpp\
    rectangle.cpp \
    startscreenlayer.cpp

HEADERS += \
    appstate.h \
    connectionlayer.h \
    gamepadcontroller.h \
    power.h \
    rocket.h\
    player.h\
    options.h\
    banana.h \
    bomb.h \
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
    maptranslator.h \
    mqttdialog.h \
    optionslayer.h \
    registerlayer.h \
    startscreenlayer.h \
    vehicleproperties.h\
    mapinfo.h \
    rectangle.h

resources.files = \
    options.txt
resources.prefix = /

RESOURCES += \
    banana.qrc \
    banana2.qrc \
    bike.qrc \
    bomb.qrc \
    car.qrc \
    powers.qrc \
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
