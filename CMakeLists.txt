cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
if(APPLE)
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
endif ()
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread -Wall -Werror -Wextra -O3 -fopenmp")

project(A3_Parallels)

include_directories(
        ${PROJECT_SOURCE_DIR}/src/Extern/Graph/include
        ${PROJECT_SOURCE_DIR}/src/Extern/Graph/internal

        ${PROJECT_SOURCE_DIR}/src/Extern/Console/

        ${PROJECT_SOURCE_DIR}/src/Extern/Matrix/include
        ${PROJECT_SOURCE_DIR}/src/Extern/Matrix/internal

        ${PROJECT_SOURCE_DIR}/src/Extern/FileManager/include
        ${PROJECT_SOURCE_DIR}/src/Extern/FileManager/internal

        ${PROJECT_SOURCE_DIR}/src/Model
        ${PROJECT_SOURCE_DIR}/src/Model/AntColony
        ${PROJECT_SOURCE_DIR}/src/Model/AntColony/ant
        ${PROJECT_SOURCE_DIR}/src/Model/Gauss
        ${PROJECT_SOURCE_DIR}/src/Model/Winograd

        ${PROJECT_SOURCE_DIR}/src/Controller

        ${PROJECT_SOURCE_DIR}/src/View
        ${PROJECT_SOURCE_DIR}/src/View/base
)

file(GLOB_RECURSE HEADER_FILES
        "${PROJECT_SOURCE_DIR}/src/*.h"
)

add_executable(
        AntView
        ${HEADER_FILES}
        src/Controller/controller.cc
        src/View/base/base_view.cc
        src/View/views.cc
        src/Model/model.cc
        src/Model/AntColony/ant_colony.cc
        src/Model/AntColony/ant/ant.cc
        src/main.cc)

target_compile_definitions(AntView PRIVATE ANT_COLONY)

add_executable(
        GaussView
        ${HEADER_FILES}
        src/Controller/controller.cc
        src/View/base/base_view.cc
        src/View/views.cc
        src/Model/model.cc
        src/Model/Gauss/gauss.cc
        src/main.cc
)

target_compile_definitions(GaussView PRIVATE GAUSS)

add_executable(
        WinogradView
        ${HEADER_FILES}
        src/Controller/controller.cc
        src/View/base/base_view.cc
        src/View/views.cc
        src/Model/model.cc
        src/Model/Winograd/winograd.cc
        src/main.cc
)

target_compile_definitions(WinogradView PRIVATE WINOGRAD)
