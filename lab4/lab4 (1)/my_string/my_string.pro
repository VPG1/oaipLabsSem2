QT -= gui

TEMPLATE = lib
DEFINES += MY_STRING_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    my_string.cpp

HEADERS += \
    my_string_global.h \
    my_string.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_func-Desktop-Debug/release/ -lmy_func
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_func-Desktop-Debug/debug/ -lmy_func
#else:unix: LIBS += -L$$PWD/../build-my_func-Desktop-Debug/ -lmy_func

#INCLUDEPATH += $$PWD/../my_func
#DEPENDPATH += $$PWD/../my_func

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-my_func-Qt_6_2_4_for_macOS-Release/release/ -lmy_func.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-my_func-Qt_6_2_4_for_macOS-Release/debug/ -lmy_func.1.0.0
else:unix: LIBS += -L$$PWD/../build-my_func-Qt_6_2_4_for_macOS-Release/ -lmy_func.1.0.0

INCLUDEPATH += $$PWD/../my_func
DEPENDPATH += $$PWD/../my_func
