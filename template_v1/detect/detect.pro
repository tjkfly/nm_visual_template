TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        get_image.cpp \
        main.cpp \
        thread_process.cpp
INCLUDEPATH += F:\software\IDE\opencv\opencv-4.4.0\op_build\install\include
LIBS += F:\software\IDE\opencv\opencv-4.4.0\op_build\install\x64\mingw\bin\libopencv_*.dll

HEADERS += \
    get_image.h \
    thread_process.h
