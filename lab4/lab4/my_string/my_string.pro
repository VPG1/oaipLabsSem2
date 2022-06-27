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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../my_func/release/ -lmy_func
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../my_func/debug/ -lmy_func
else:unix: LIBS += -L$$OUT_PWD/../my_func/ -lmy_func

INCLUDEPATH += $$PWD/../my_func
DEPENDPATH += $$PWD/../my_func
