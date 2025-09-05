QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    approverpage.cpp \
    database.cpp \
    designerpage.cpp \
    main.cpp \
    mainwindow.cpp \
    managerpage.cpp

HEADERS += \
    approverpage.h \
    database.h \
    designerpage.h \
    mainwindow.h \
    managerpage.h

FORMS += \
    approverpage.ui \
    designerpage.ui \
    mainwindow.ui \
    managerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
