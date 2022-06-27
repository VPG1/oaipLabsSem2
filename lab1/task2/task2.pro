QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    figures/circle.cpp \
    figures/eightpointedstar.cpp \
    figures/fivepointedstar.cpp \
    figures/hexagon.cpp \
    figures/npointedstar.cpp \
    figures/polygon.cpp \
    figures/rectangle.cpp \
    figures/rhombus.cpp \
    figures/shape.cpp \
    figures/sixpointedstar.cpp \
    figures/square.cpp \
    figures/triangle.cpp \
    main.cpp \
    matrix.cpp \
    widgets/abstractadjustmentwidget.cpp \
    widgets/circleadjustmentwidet.cpp \
    widgets/coordinput.cpp \
    widgets/graphicsscene.cpp \
    widgets/hexagonadjustmentwidget.cpp \
    widgets/rectangleadjustmentwidget.cpp \
    widgets/rhombusadjustmentwidget.cpp \
    widgets/squareadjustmentwidget.cpp \
    widgets/staradjustmentwidget.cpp \
    widgets/triangleadjustmentwidget.cpp \
    widgets/widget.cpp

HEADERS += \
    figures/circle.h \
    figures/eightpointedstar.h \
    figures/fivepointedstar.h \
    figures/hexagon.h \
    figures/npointedstar.h \
    figures/polygon.h \
    figures/rectangle.h \
    figures/rhombus.h \
    figures/shape.h \
    figures/sixpointedstar.h \
    figures/square.h \
    figures/triangle.h \
    matrix.h \
    widgets/abstractadjustmentwidget.h \
    widgets/circleadjustmentwidet.h \
    widgets/coordinput.h \
    widgets/graphicsscene.h \
    widgets/hexagonadjustmentwidget.h \
    widgets/rectangleadjustmentwidget.h \
    widgets/rhombusadjustmentwidget.h \
    widgets/squareadjustmentwidget.h \
    widgets/staradjustmentwidget.h \
    widgets/triangleadjustmentwidget.h \
    widgets/widget.h

INCLUDEPATH += \
    figures \
    widgets

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
