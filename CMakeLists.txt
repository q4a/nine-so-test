cmake_minimum_required(VERSION 3.18)
project(nine-so-test)

option(SINGLE_BIN "Build single bin=ON or create so lib=OFF" OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

### Set up output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)

if (SINGLE_BIN)
    set(MY_LINK_TARGET ${PROJECT_NAME})
    set(SRC_FILES
        "d3dtester.cpp"
        "d3dtester.h"
        "main.cpp"
    )
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
else()
    set(SO_LIB_NAME "d3dtester")
    set(MY_LINK_TARGET ${SO_LIB_NAME})
    add_library(${MY_LINK_TARGET} SHARED
        "d3dtester.cpp"
        "d3dtester.h"
    )
    add_executable(${PROJECT_NAME} WIN32 "main.cpp")
endif()

# Dependencies

if (WIN32)
    message("TODO: use Windows D3D9 API")
else()
    message("Using Gallium Nine for native D3D9 API")

    #sudo apt install libd3dadapter9-mesa-dev
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(D3D REQUIRED IMPORTED_TARGET d3d)
    #sudo apt install libsdl2-dev
    set(SDL_DEPS "SDL2")

    include(ExternalProject)
    ExternalProject_Add(nine-native
        GIT_REPOSITORY    https://github.com/q4a/nine-native
        GIT_TAG           main
        GIT_SHALLOW       ON
        BUILD_ALWAYS      OFF
        BUILD_BYPRODUCTS  <BINARY_DIR>/libnine-native.a
        CMAKE_ARGS        -DCMAKE_BUILD_TYPE=Debug -DNINE_POSITION_INDEPENDENT=ON
        INSTALL_COMMAND   ""
    )
    ExternalProject_Get_property(nine-native SOURCE_DIR BINARY_DIR)
    set(NINE_NATIVE_INCLUDE_DIRS
        "${SOURCE_DIR}/include"
        "${SOURCE_DIR}/include/D3D9"
        "${SOURCE_DIR}/include/windows"
    )
    set(NATIVE_D3D9_LIBS
        "${BINARY_DIR}/libnine-native.a"
        ${SDL_DEPS}
        X11
        xcb
        xcb-present
        xcb-dri3
        xcb-xfixes
        X11-xcb
    )
    include_directories("${NINE_NATIVE_INCLUDE_DIRS}")
    add_dependencies(${MY_LINK_TARGET} nine-native)
endif()

if (SINGLE_BIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${NATIVE_D3D9_LIBS}
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SO_LIB_NAME}
    )
    target_link_libraries(${SO_LIB_NAME} PRIVATE
        ${NATIVE_D3D9_LIBS}
    )
endif()
