cmake_minimum_required(VERSION 3.0)
option(ARM_BUILD "Build on ARM" OFF)

set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/aarch64-linux-gnu-g++)
set(CMAKE_C_COMPILER ${TOOLCHAIN}/aarch64-linux-gnu-gcc)
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN})

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

project(SimpleLibrary)

include_directories(include)
add_subdirectory(src)

add_executable(Main main.cpp)
add_executable(MainLib main_lib.cpp)
set_property(TARGET MainLib PROPERTY PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/buffer.h")
target_link_libraries(MainLib buffer)

install(
    TARGETS Main MainLib
    DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

