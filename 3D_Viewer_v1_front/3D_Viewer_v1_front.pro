QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    ../3D_Viewer.c \
    ../affine_transformations.c \
    ../set_centre.c


HEADERS += \
    myopenglwidget.h \
    mainwindow.h \
    ../3D_Viewer.h


FORMS += \
    mainwindow.ui

linux: {
    INCLUDEPATH += /usr/include/GL
    LIBS += -lGL -lGLU
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
