QT       += core gui mqtt gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/mapobjects/checkpoint/checkpoint.cpp \
    game/mapobjects/circle/circle.cpp \
    game/mapobjects/player/player.cpp\
    game/mapobjects/rectangle/rectangle.cpp \
    game/ui/animatedbackground.cpp \
    game/ui/connectionlayer/connectionlayer.cpp \
    game/ui/gamescreen/gamescreen.cpp \
    game/ui/generics/uibutton.cpp \
    game/ui/mainwindow.cpp \
    game/ui/optionslayer/optionslayer.cpp \
    game/ui/registerlayer/registerlayer.cpp \
    game/ui/startscreenlayer/startscreenlayer.cpp \
    game/controller/controlleradapter.cpp \
    game/controller/controllermanager.cpp \
    game/controller/gamepad/gamepadcontroller.cpp \
    game/controller/keyboard/keyboardcontroller.cpp \
    game/powerups/banana/banana.cpp \
    game/powerups/bomb/bomb.cpp \
    game/powerups/power.cpp \
    game/powerups/rocket/rocket.cpp\
    game/utils/properties/gameproperties.cpp \
    game/utils/map/mapinfo.cpp \
    game/utils/map/maptranslator.cpp \
    game/utils/mqtt/mqttdialog.cpp \
    game/utils/options.cpp \
    game/utils/resourceloader.cpp \
    main.cpp

HEADERS += \
    game/ui/animatedbackground.h \
    game/ui/generics/uibutton.h \
    game/utils/appstate.h \
    game/utils/resourceloader.h \
    game/utils/options.h \
    game/utils/properties/gameproperties.h \
    game/utils/map/maptranslator.h \
    game/utils/mqtt/mqttdialog.h \
    game/utils/properties/vehicleproperties.h\
    game/utils/map/mapinfo.h \
    game/ui/gamescreen/gamescreen.h \
    game/ui/connectionlayer/connectionlayer.h \
    game/ui/displayview.h \
    game/ui/mainwindow.h \
    game/ui/optionslayer/optionslayer.h \
    game/ui/registerlayer/registerlayer.h \
    game/ui/startscreenlayer/startscreenlayer.h \
    game/controller/gamepad/gamepadcontroller.h \
    game/controller/controlleradapter.h \
    game/controller/controllermanager.h \
    game/controller/keyboard/keyboardcontroller.h \
    game/powerups/power.h \
    game/powerups/rocket/rocket.h\
    game/powerups/banana/banana.h \
    game/powerups/bomb/bomb.h \
    game/mapobjects/player/player.h\
    game/mapobjects/checkpoint/checkpoint.h \
    game/mapobjects/circle/circle.h \
    game/mapobjects/circuitelement.h \
    game/mapobjects/rectangle/rectangle.h

resources.files = \
    options.txt
resources.prefix = /

RESOURCES += \
    game/powerups/banana/banana.qrc \
    game/powerups/banana/banana2.qrc \
    game/powerups/bomb/bomb.qrc \
    game/powerups/powers.qrc \
    game/powerups/rocket/rocket.qrc \
    game/mapobjects/vehicles/bike.qrc \
    game/mapobjects/vehicles/car.qrc \
    game/mapobjects/vehicles/missing_texture.qrc \
    game/mapobjects/vehicles/truck.qrc \
    game/ui/generics/uibutton.qrc \
    game/ui/startscreenlayer/start_background.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

