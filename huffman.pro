TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    compressao.c \
    freq_w.c \
    adt.c \
    bitop.c \
    descompressao.c

HEADERS += \
    compressao.h \
    freq_w.h \
    adt.h \
    bitop.h \
    descompressao.h
