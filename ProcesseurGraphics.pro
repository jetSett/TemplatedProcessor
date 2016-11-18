#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T13:04:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcesseurGraphics
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    metaprog.cpp \
    processor.cpp \
    Util.cpp \
    Operands/add.cpp \
    Operands/and.cpp \
    Operands/asr.cpp \
    Operands/call.cpp \
    Operands/jumpReturn.cpp \
    Operands/leth.cpp \
    Operands/letl.cpp \
    Operands/lsl.cpp \
    Operands/lsr.cpp \
    Operands/or.cpp \
    Operands/rmemCopy.cpp \
    Operands/snif.cpp \
    Operands/sub.cpp \
    Operands/wmem.cpp \
    Operands/xor.cpp

HEADERS  += widget.hpp \
    metaprog.hpp \
    processor.hpp \
    Util.hpp

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++14 -ftemplate-depth=1000000000
