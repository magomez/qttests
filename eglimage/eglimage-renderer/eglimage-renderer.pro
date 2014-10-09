QT += opengl widgets

CONFIG += link_pkgconfig
PKGCONFIG += egl glesv2

HEADERS = renderer.h \

SOURCES = renderer.cpp \
          main.cpp
