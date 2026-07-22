cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall")  #-DCMAKE_BUILD_TYPE=DEBUG
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
message (STATUS "BUILDING")
project (STOCBIONET C CXX)
find_package(Threads REQUIRED)
set (CMAKE_CXX_STANDARD 11)
message (STATUS "SETTING PATHS")
set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set ( SRC_DIR "${ROOT}/src")
message (STATUS "ADDING FOLDERS")
list ( APPEND DIRS
    "${SRC_DIR}"
    "${SRC_DIR}/delay_structures"
    "${SRC_DIR}/Log"
    "${SRC_DIR}/Dependency_Graph"
    "${SRC_DIR}/model"
    "${SRC_DIR}/sbml"
    )
file (GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)
file (GLOB_RECURSE HRCS ${SRC_DIR}/*.hpp)
list (FILTER SRCS EXCLUDE REGEX ".*/main.cpp$")
list (FILTER SRCS EXCLUDE REGEX ".*/gui/.*")
add_library(stocbionet_core ${SRCS} ${HRCS})
target_include_directories (stocbionet_core PUBLIC ${DIRS})

find_package(PkgConfig QUIET)
if (PkgConfig_FOUND)
    pkg_check_modules(LIBSBML QUIET libsbml)
endif()
if (LIBSBML_FOUND)
    target_compile_definitions(stocbionet_core PUBLIC STOCBIONET_HAVE_LIBSBML)
    target_include_directories(stocbionet_core PUBLIC ${LIBSBML_INCLUDE_DIRS})
    target_link_libraries(stocbionet_core PUBLIC ${LIBSBML_LIBRARIES})
    message(STATUS "SBML support enabled through libSBML")
else()
    message(WARNING "libSBML not found; SBML files will report a runtime error")
endif()

add_executable(Stocbionet src/main.cpp)
target_link_libraries(Stocbionet PRIVATE stocbionet_core)

if (PkgConfig_FOUND)
    pkg_check_modules(GTK4 QUIET gtk4)
    pkg_check_modules(ADWAITA QUIET libadwaita-1)
endif()
if (GTK4_FOUND AND ADWAITA_FOUND)
    add_executable(StocbionetGui src/gui/main_gui.cpp)
    target_include_directories(StocbionetGui PRIVATE ${GTK4_INCLUDE_DIRS} ${ADWAITA_INCLUDE_DIRS})
    target_link_libraries(StocbionetGui PRIVATE stocbionet_core Threads::Threads ${GTK4_LIBRARIES} ${ADWAITA_LIBRARIES})
    target_compile_options(StocbionetGui PRIVATE ${GTK4_CFLAGS_OTHER} ${ADWAITA_CFLAGS_OTHER})
    message(STATUS "GTK/libadwaita GUI enabled")
else()
    message(WARNING "GTK4/libadwaita not found; GUI target will not be built")
endif()
