QT += opengl widgets core-private gui-private

CONFIG += link_pkgconfig
PKGCONFIG += egl glesv2

HEADERS = widget.h \

SOURCES = widget.cpp \
          main.cpp
