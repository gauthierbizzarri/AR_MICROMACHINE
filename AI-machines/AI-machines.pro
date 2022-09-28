QT -= gui
QT += mqtt

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ai.cpp \
        ai_manager.cpp \
        fakebroker.cpp \
        main.cpp \
        qtmqtttalker.cpp

TRANSLATIONS += \
    AI-machines_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ai.h \
    ai_manager.h \
    fakebroker.h \
    qtmqtttalker.h
