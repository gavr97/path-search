cmake_minimum_required(VERSION 3.5)
project(repo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TINY_XML tinyxml/tinyxml2.h tinyxml/tinyxml2.cpp)
set(GLOBAL global/globalVars.h global/globalTypes.h)
set(DATA_CODE dataCode/myTask.h dataCode/myTask.cpp dataCode/myOutput.h dataCode/myOutput.cpp)
set(ALGORITHM main.cpp algorithm/astar.h algorithm/astar.cpp algorithm/myHeap.h algorithm/myNode.cpp algorithm/myNode.h)
set(LOGGER logger/myLog.h logger/myLog.cpp)

add_executable(repo ${TINY_XML} ${GLOBAL} ${DATA_CODE} ${ALGORITHM} ${LOGGER})