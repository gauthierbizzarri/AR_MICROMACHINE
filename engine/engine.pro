QT       += core gui widgets mqtt gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    game_checkpoint.cpp \
    game_circle.cpp \
    game_engine.cpp \
    game_entity.cpp \
    game_map.cpp \
    game_map_object.cpp \
    game_obstacle.cpp \
    game_player.cpp \
    game_properties.cpp \
    game_rectangle.cpp \
    game_sketch.cpp \
    main.cpp \
    ihm.cpp

HEADERS += \
    client.h \
    controller.h \
    game_checkpoint.h \
    game_circle.h \
    game_engine.h \
    game_entity.h \
    game_map.h \
    game_map_object.h \
    game_obstacle.h \
    game_player.h \
    game_properties.h \
    game_rectangle.h \
    game_sketch.h \
    ihm.h \
    main.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
