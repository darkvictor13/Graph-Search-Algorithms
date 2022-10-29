cmake_minimum_required(VERSION 3.0.0)
project(Graph_Search_Algorithms VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(CMAKE_CXX_STANDARD 20)

# Get all src files
set(SRC_DIR ../src)
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

set(CMAKE_SOURCE_DIR ${SRC_DIR})

add_executable(${PROJECT_NAME}_${PROJECT_VERSION}.out ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
