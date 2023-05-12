#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T01:19:28
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = othello
TEMPLATE = app


SOURCES += main/main.cpp\
        main/mainwindow.cpp \
        board/board.cpp \
        board/square.cpp \
        player/player.cpp \
        player/humanplayer.cpp \
        player/computerplayer.cpp \
        ai.cpp \
        ui/uisquare.cpp \
        ui/uigamescene.cpp \
        gamelogic/gameengine.cpp

HEADERS  += main/mainwindow.h \
        board/board.h \
        board/square.h \
        player/player.h \
        player/humanplayer.h \
        player/computerplayer.h \
        ai.h \
        ui/uisquare.h \
        ui/uigamescene.h \
        gamelogic/gameengine.h

FORMS    += main/mainwindow.ui
