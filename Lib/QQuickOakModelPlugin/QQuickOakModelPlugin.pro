# oakmodelview - version 0.1.0
# --------------------------------------------------------
# Copyright (C) 2017, by Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
# Report bugs and download new versions at http://oakmodelview.com/
#
# This library is distributed under the MIT License.
# See accompanying file LICENSE in the root folder.

TEMPLATE = lib
CONFIG += plugin
CONFIG += c++1z
QT += qml quick

TARGET = oakmodelplugin

DEFINES += XML_BACKEND
DEFINES += NOMINMAX

DESTDIR += ../Plugins/Oak/Model

INCLUDEPATH += \
    . \
    .. \
    ../OakXML \
    ../OakModel \
    ../QOakModel

	
HEADERS += \
    oakmodelplugin.h


SOURCES += \
    oakmodelplugin.cpp

# Make the qmldir file visible in the Project tree
OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR
COPIES += cpqmldir


TARGET = $$qtLibraryTarget($$TARGET)

CONFIG(debug, debug|release) {
    win32:POST_TARGETDEPS = \
        ../OakXMLd.lib \
        ../OakModeld.lib \
        ../QOakModeld.lib
    win32:LIBS = \
        ../OakXMLd.lib \
        ../OakModeld.lib \
        ../QOakModeld.lib
    OBJECTS_DIR = ./debug
} else {
    win32:POST_TARGETDEPS = \
        ../OakXML.lib \
        ../OakModel.lib \
        ../QOakModel.lib
    win32:LIBS = \
        ../OakXML.lib \
        ../OakModel.lib \
        ../QOakModel.lib
    OBJECTS_DIR = ./release
}

##### Stuff needed by the installer #####

#DESTPATH = ../../installer

#target.files += files.qml
#target.path = $$DESTPATH

#qmldir.files = $$PWD/qmldir
#qmldir.path  =$$DESTPATH

#INSTALLS += target qmldir

#CONFIG += install_ok  # Do not cargo-cult this!

