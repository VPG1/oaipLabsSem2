QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    function.cpp \
    main.cpp \
    parser.cpp \
    token.cpp \
    tokenizer.cpp \
    tokentype.cpp \
    type.cpp \
    variable.cpp \
    widget.cpp

HEADERS += \
    function.h \
    parser.h \
    token.h \
    tokenizer.h \
    tokentype.h \
    type.h \
    variable.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

## pair
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_pair-Desktop-Debug/release/ -lmy_pair
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_pair-Desktop-Debug/debug/ -lmy_pair
#else:unix: LIBS += -L$$PWD/../build-my_pair-Desktop-Debug/ -lmy_pair

#INCLUDEPATH += $$PWD/../my_pair
#DEPENDPATH += $$PWD/../my_pair

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_pair-Desktop-Debug/release/libmy_pair.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_pair-Desktop-Debug/debug/libmy_pair.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_pair-Desktop-Debug/release/my_pair.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_pair-Desktop-Debug/debug/my_pair.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../build-my_pair-Desktop-Debug/libmy_pair.a

## string
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_string-Desktop-Debug/release/ -lmy_string
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_string-Desktop-Debug/debug/ -lmy_string
#else:unix: LIBS += -L$$PWD/../build-my_string-Desktop-Debug/ -lmy_string

#INCLUDEPATH += $$PWD/../my_string
#DEPENDPATH += $$PWD/../my_string

## cstr function
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_func-Desktop-Debug/release/ -lmy_func
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_func-Desktop-Debug/debug/ -lmy_func
#else:unix: LIBS += -L$$PWD/../build-my_func-Desktop-Debug/ -lmy_func

#INCLUDEPATH += $$PWD/../my_func
#DEPENDPATH += $$PWD/../my_func


## vector
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/release/ -lmy_vector
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/debug/ -lmy_vector
#else:unix: LIBS += -L$$PWD/../build-my_vector-Desktop-Debug/ -lmy_vector

#INCLUDEPATH += $$PWD/../my_vector
#DEPENDPATH += $$PWD/../my_vector

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_vector-Desktop-Debug/release/libmy_vector.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_vector-Desktop-Debug/debug/libmy_vector.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_vector-Desktop-Debug/release/my_vector.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-my_vector-Desktop-Debug/debug/my_vector.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../build-my_vector-Desktop-Debug/libmy_vector.a
