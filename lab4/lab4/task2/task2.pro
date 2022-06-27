QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binarynum.cpp \
    main.cpp \
    timer.cpp \
    widget.cpp

HEADERS += \
    binarynum.h \
    timer.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/release/ -lmy_vector
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/debug/ -lmy_vector
#else:unix: LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/ -lmy_vector

#INCLUDEPATH += $$PWD/../my_vector
#DEPENDPATH += $$PWD/../my_vector

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../my_vector/release/ -lmy_vector
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../my_vector/debug/ -lmy_vector
else:unix: LIBS += -L$$OUT_PWD/../my_vector/ -lmy_vector

INCLUDEPATH += $$PWD/../my_vector
DEPENDPATH += $$PWD/../my_vector

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../my_vector/release/libmy_vector.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../my_vector/debug/libmy_vector.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../my_vector/release/my_vector.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../my_vector/debug/my_vector.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../my_vector/libmy_vector.a
