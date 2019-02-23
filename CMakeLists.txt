cmake_minimum_required (VERSION 3.1)
message (STATUS "BUILDING")
project (SSA C CXX)
set (CMAKE_CXX_STANDARD 11)
message (STATUS "SETTING PATHS")
set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set ( SRC_DIR "${ROOT}/src")
set ( HEADERS_DIR "${ROOT}/include")
message (STATUS "ADDING FOLDERS")
list ( APPEND SDIRS
    "${SRC_DIR}"
    "${SRC_DIR}/delay_structures"
    "${SRC_DIR}/Log"
    "${SRC_DIR}/Dependency_Graph"
    "${SRC_DIR}/model"
    )
list ( APPEND HDIRS
    "${HEADERS_DIR}"
    "${HEADERS_DIR}/delay_structures"
    "${HEADERS_DIR}/Log"
    "${HEADERS_DIR}/Dependency_Graph"
    "${HEADERS_DIR}/model"
    )
file (GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)
file (GLOB_RECURSE HRCS ${HEADERS_DIR}/*.hpp)
include_directories (${HDIRS})
add_executable(SSA ${SRCS} ${HRCS})
