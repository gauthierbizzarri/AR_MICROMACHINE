QT       += core gui mqtt gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/mapobjects/checkpoint/checkpoint.cpp \
    game/mapobjects/circle/circle.cpp \
    game/ui/connectionlayer/connectionlayer.cpp \
    game/controller/controlleradapter.cpp \
    game/controller/controllermanager.cpp \
    game/powerups/banana/banana.cpp \
    game/powerups/bomb/bomb.cpp \
    game/controller/gamepad/gamepadcontroller.cpp \
    game/utils/properties/gameproperties.cpp \
    game/ui/gamescreen/gamescreen.cpp \
    game/controller/keyboard/keyboardcontroller.cpp \
    main.cpp \
    game/ui/mainwindow.cpp \
    game/utils/map/mapinfo.cpp \
    game/utils/map/maptranslator.cpp \
    game/utils/mqtt/mqttdialog.cpp \
    game/utils/options.cpp \
    game/ui/optionslayer/optionslayer.cpp \
    game/mapobjects/player/player.cpp\
    game/ui/registerlayer/registerlayer.cpp \
    game/powerups/power.cpp \
    game/utils/resourceloader.cpp \
    game/powerups/rocket/rocket.cpp\
    game/mapobjects/rectangle/rectangle.cpp \
    game/ui/startscreenlayer/startscreenlayer.cpp

HEADERS += \
    game/utils/appstate.h \
    game/ui/connectionlayer/connectionlayer.h \
    game/controller/gamepad/gamepadcontroller.h \
    game/powerups/power.h \
    game/utils/resourceloader.h \
    game/powerups/rocket/rocket.h\
    game/mapobjects/player/player.h\
    game/utils/options.h\
    game/powerups/banana/banana.h \
    game/powerups/bomb/bomb.h \
    game/mapobjects/checkpoint/checkpoint.h \
    game/mapobjects/circle/circle.h \
    game/mapobjects/circuitelement.h \
    game/controller/controlleradapter.h \
    game/controller/controllermanager.h \
    game/ui/displayview.h \
    game/utils/properties/gameproperties.h \
    game/ui/gamescreen/gamescreen.h \
    game/controller/keyboard/keyboardcontroller.h \
    game/ui/mainwindow.h \
    game/utils/map/maptranslator.h \
    game/utils/mqtt/mqttdialog.h \
    game/ui/optionslayer/optionslayer.h \
    game/ui/registerlayer/registerlayer.h \
    game/ui/startscreenlayer/startscreenlayer.h \
    game/utils/properties/vehicleproperties.h\
    game/utils/map/mapinfo.h \
    game/mapobjects/rectangle/rectangle.h

resources.files = \
    options.txt
resources.prefix = /

RESOURCES += \
    game/powerups/banana/banana.qrc \
    game/powerups/banana/banana2.qrc \
    game/mapobjects/vehicles/bike.qrc \
    game/powerups/bomb/bomb.qrc \
    game/mapobjects/vehicles/car.qrc \
    game/powerups/powers.qrc \
    game/mapobjects/vehicles/missing_texture.qrc \
    game/powerups/rocket/rocket.qrc \
    game/mapobjects/vehicles/truck.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

