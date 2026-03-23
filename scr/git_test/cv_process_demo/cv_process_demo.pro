QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imagelabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    imageconverter.h \
    imagelabel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# OpenCV配置 - Windows MSVC环境
# 配置opencv4
INCLUDEPATH += F:/opencv/build/include \
               F:/opencv/build/include/opencv2
Debug:
{
    LIBS += -lF:/opencv/build/x64/vc15/lib/opencv_world460d
}
Release:
{
    LIBS += -lF:/opencv/build/x64/vc15/lib/opencv_world460
}
