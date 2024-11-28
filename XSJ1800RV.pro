QT += core gui
QT += network
QT += serialport
QT += serialport network
QT += websockets
QT += charts
QT += sql
#QT += qml
#include(src/xlsx/qtxlsx.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarmlog_widget.cpp \
    camera_widget.cpp \
    canshu_widget.cpp \
    data_thread.cpp \
    history_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    mian_widget.cpp \
    net_widget.cpp \
    keyboard.cpp \
    keyboard_ABC.cpp \
    serialport.cpp \
    sqlite.cpp \
    tcp_socket.cpp \
    xitong_widget.cpp \
    ceventfilter.cpp
HEADERS += \
    alarmlog_widget.h \
    camera_widget.h \
    canshu_widget.h \
    data_thread.h \
    history_widget.h \
    mainwindow.h \
    mian_widget.h \
    net_widget.h \
    keyboard.h \
    keyboard_ABC.h \
    serialport.h \
    sqlite.h \
    tcp_socket.h \
    xitong_widget.h \
    ceventfilter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    alarmlog_widget.ui \
    camera_widget.ui \
    canshu_widget.ui \
    history_widget.ui \
    mian_widget.ui \
    net_widget.ui \
    keyboard.ui \
    keyboard_ABC.ui \
    xitong_widget.ui

RESOURCES += \
    images.qrc
