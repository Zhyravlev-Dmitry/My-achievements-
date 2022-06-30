cmake_minimum_required(VERSION 3.5)
add_library( my_lib SHARED
        lib.h
        lib.cpp
        )
set_target_properties(my_lib PROPERTIES LINKER_LANGUAGE CXX)
