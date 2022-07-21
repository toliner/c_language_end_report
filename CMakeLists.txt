cmake_minimum_required(VERSION 3.22)
project(c_language_end_report)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /execution-charset:SHIFT_JIS /source-charset:UTF-8")

include_directories(PDCurses)
add_link_options(/stack:128000000)
link_libraries(${CMAKE_SOURCE_DIR}/PDCurses/pdcurses.lib)

add_executable(
        c_language_end_report
        Setting.c
        Setting.h
        data.cpp data.h sort.cpp sort.h
        main.cpp
)
