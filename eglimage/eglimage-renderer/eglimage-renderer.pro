QT += opengl widgets core-private gui-private

CONFIG += link_pkgconfig
PKGCONFIG += egl glesv2

HEADERS = renderer.h \

SOURCES = renderer.cpp \
          main.cpp
