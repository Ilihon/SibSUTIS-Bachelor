QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    change_command_widget.cpp \
    change_list_my_item_widget.cpp \
    command_widget.cpp \
    funnyplace_widget.cpp \
    hello_box.cpp \
    hello_box_2.cpp \
    list_my_document_widget.cpp \
    list_my_item_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    mydatabase.cpp \
    sleephouse_widget.cpp \
    transfer_widget.cpp \
    workplace_widget.cpp

HEADERS += \
    change_command_widget.h \
    change_list_my_item_widget.h \
    command_widget.h \
    funnyplace_widget.h \
    hello_box.h \
    hello_box_2.h \
    list_my_document_widget.h \
    list_my_item_widget.h \
    mainwindow.h \
    mydatabase.h \
    sleephouse_widget.h \
    transfer_widget.h \
    workplace_widget.h

FORMS += \
    change_command_widget.ui \
    change_list_my_item_widget.ui \
    command_widget.ui \
    funnyplace_widget.ui \
    hello_box.ui \
    hello_box_2.ui \
    list_my_document_widget.ui \
    list_my_item_widget.ui \
    mainwindow.ui \
    sleephouse_widget.ui \
    transfer_widget.ui \
    workplace_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
