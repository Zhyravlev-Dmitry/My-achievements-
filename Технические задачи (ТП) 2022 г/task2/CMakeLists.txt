cmake_minimum_required( VERSION 3.5 )
project( task2 )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${task2_SOURCE_DIR}/lib )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${task2_SOURCE_DIR}/bin)

execute_process(COMMAND python3 preparing.py WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/A)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable( C C/main.cpp )
add_executable( CTest
        C/main_test.cpp
        C/test.cpp
        )

add_subdirectory(B)

target_include_directories(
        CTest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GTEST_INCLUDE_DIRS}
)

target_link_libraries( C my_lib )
target_link_libraries( CTest my_lib Threads::Threads ${GTEST_LIBRARIES})

target_include_directories(C PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(CTest PUBLIC ${PROJECT_SOURCE_DIR})

enable_testing()
gtest_discover_tests(CTest)

