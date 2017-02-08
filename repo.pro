TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    algorithm/astar.cpp \
    algorithm/myNode.cpp \
    dataCode/myOutput.cpp \
    dataCode/myTask.cpp \
    global/globalVars.cpp \
    logger/myLog.cpp \
    tinyxml/tinyxml2.cpp

DISTFILES += \
    algorithm/astar.h.gch \
    algorithm/myHeap.h.gch \
    dataCode/myTask.h.gch \
    logger/myLog.h.gch \
    tinyxml/tinyxml2.h.gch

HEADERS += \
    algorithm/astar.h \
    algorithm/myHeap.h \
    algorithm/myNode.h \
    dataCode/myOutput.h \
    dataCode/myTask.h \
    global/globalTypes.h \
    global/globalVars.h \
    logger/myLog.h \
    tinyxml/tinyxml2.h
