cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")  #-DCMAKE_BUILD_TYPE=DEBUG
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
message (STATUS "BUILDING")
project (SSA C CXX)
set (CMAKE_CXX_STANDARD 11)
message (STATUS "SETTING PATHS")
set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set ( SRC_DIR "${ROOT}/src")
#set ( HEADERS_DIR "${ROOT}/include")
message (STATUS "ADDING FOLDERS")
list ( APPEND DIRS
    "${SRC_DIR}"
    "${SRC_DIR}/delay_structures"
    "${SRC_DIR}/Log"
    "${SRC_DIR}/Dependency_Graph"
    "${SRC_DIR}/model"
    )
file (GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)
file (GLOB_RECURSE HRCS ${SRC_DIR}/*.hpp)
include_directories (${DIRS})
add_executable(SSA ${SRCS} ${HRCS})
