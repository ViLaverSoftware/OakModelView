TEMPLATE = lib
CONFIG += plugin
CONFIG += c++1z
QT += qml quick

TARGET = oakviewplugin

DEFINES += XML_BACKEND
DEFINES += NOMINMAX

DESTDIR += ../Plugins/Oak/View

INCLUDEPATH += \
    . \
    .. \
    ../OakXML \
    ../OakModel \
    ../QtOakModel

	
HEADERS += \
    oakmodelplugin.h

SOURCES += \
    oakmodelplugin.cpp

DISTFILES += \
    OakToolButton.qml \
    OakToolTip.qml

include(Delegates.pri)
include(ToolBars.pri)

# Make the qmldir file visible in the Project tree
OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR

cpqml.files = $$DISTFILES
cpqml.path = $$DESTDIR

COPIES += \
    cpqmldir \
    cppicsdir \
    cpqml

TARGET = $$qtLibraryTarget($$TARGET)

CONFIG(debug, debug|release) {
    win32:POST_TARGETDEPS = \
        ../OakXMLd.lib \
        ../OakModeld.lib \
        ../Plugins\Oak\Model\oakmodelplugind.lib
    win32:LIBS = \
        ../OakXMLd.lib \
        ../OakModeld.lib \
        ../Plugins\Oak\Model\oakmodelplugind.lib
    OBJECTS_DIR = ./debug
} else {
    win32:POST_TARGETDEPS = \
        ../OakXML.lib \
        ../OakModel.lib \
        ../Plugins\Oak\Model\oakmodelplugin.lib
    win32:LIBS = \
        ../OakXML.lib \
        ../OakModel.lib \
        ../Plugins\Oak\Model\oakmodelplugin.lib
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


