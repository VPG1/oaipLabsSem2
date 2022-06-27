QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form.cpp \
    main.cpp \
    mylineedit.cpp \
    statement.cpp \
    statementdialog.cpp \
    widget.cpp

HEADERS += \
    ListAndFile.h \
    advance_and_distance.h \
    form.h \
    list.h \
    listV2.h \
    mylineedit.h \
    statement.h \
    statementdialog.h \
    widget.h

FORMS += \
    form.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
