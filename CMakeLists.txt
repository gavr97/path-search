cmake_minimum_required(VERSION 3.6)
project(repo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TINY_XML tinyxml2.h tinyxml2.cpp)
set(SOURCE_FILES main.cpp globalTypes.h myTask.h myTask.cpp astar.h astar.cpp myHeap.h myLog.h myLog.cpp globalVars.h globalVars.cpp)

add_executable(repo ${SOURCE_FILES} ${TINY_XML})