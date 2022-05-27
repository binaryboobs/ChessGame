QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    chess.cpp \
    horse.cpp \
    king.cpp \
    main.cpp \
    paintboard.cpp \
    pawn.cpp \
    queen.cpp \
    rook.cpp \
    unit.cpp \
    unitsinfo.cpp \
    utils.cpp

HEADERS += \
    chess.h \
    paintboard.h \
    unit.h \
    unitsinfo.h \
    utils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
