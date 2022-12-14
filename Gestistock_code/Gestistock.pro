QT       += sql
QT       += core gui
QT       += printsupport
QT       += widgets
QT       += core gui  serialport
QT += network
QT += core
QT += widgets
QT += svg
QT += multimedia multimediawidgets

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
    Client.cpp \
    arduino.cpp \
    commandes.cpp \
    connection.cpp \
    employe.cpp \
    finance.cpp \
    fournisseurs.cpp \
    historique.cpp \
    livraisons.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    notification.cpp \
    produits.cpp \
    qrcode.cpp \
    smtp.cpp \
    widget.cpp

HEADERS += \
    Client.h \
    arduino.h \
    commandes.h \
    connection.h \
    employe.h \
    finance.h \
    fournisseurs.h \
    historique.h \
    livraisons.h \
    mainwindow.h \
    menu.h \
    notification.h \
    produits.h \
    qrcode.h \
    smtp.h \
    widget.h

FORMS += \
    mainwindow.ui \
    menu.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc
