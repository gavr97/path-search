cmake_minimum_required(VERSION 3.5)
project(repo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TINY_XML tinyxml/tinyxml2.h tinyxml/tinyxml2.cpp)
set(GLOBAL global/globalVars.h global/globalTypes.h)
set(DATA_CODE dataCode/task.h dataCode/task.cpp dataCode/output.h dataCode/output.cpp dataCode/map.cpp dataCode/map.h)
set(ALGORITHM main.cpp algorithm/astar.h algorithm/astar.cpp algorithm/heap.h algorithm/node.cpp algorithm/close.cpp algorithm/close.h algorithm/open.cpp algorithm/open.h)
set(LOGGER logger/log.h logger/log.cpp)

add_executable(repo ${TINY_XML} ${GLOBAL} ${DATA_CODE} ${ALGORITHM} ${LOGGER})