cmake_minimum_required(VERSION 3.5)

project(Installer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /Users/mektus/Qt/6.2.0/macos)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(UI_DIR "${CMAKE_SOURCE_DIR}/screens")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${UI_DIR})
include_directories(${SRC_DIR})
include_directories(${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS} )

file(GLOB_RECURSE SOURCES
        "${UI_DIR}/*.ui"
        "${SRC_DIR}/*.cpp"
        "${SRC_DIR}/*.hpp"
        "${SRC_DIR}/*/*.cpp"
        "${SRC_DIR}/*/*.hpp")

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${UI_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_executable(Installer ${SOURCES} src/abstract_screen.hpp src/types/types.cpp src/utils/utils.hpp src/utils/utils.cpp)
endif()

target_include_directories(Installer PRIVATE ${UI_DIR})
target_include_directories(Installer PRIVATE ${SRC_DIR})

target_link_libraries(Installer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Installer PRIVATE Qt${QT_VERSION_MAJOR}::Network)

