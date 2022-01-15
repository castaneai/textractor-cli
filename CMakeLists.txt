cmake_minimum_required(VERSION 3.21)
project(hookcli)

set(CMAKE_CXX_STANDARD 17)

add_executable(hookcli main.cpp)

add_compile_options(
        /std:c++17
        /MP
        /wd4018 # signed/unsigned mismatch
        /DVERSION="${VERSION}"
        /DUNICODE # config.pri
        /D_UNICODE
)

include_directories(./Textractor/include ./Textractor/host)

target_precompile_headers(hookcli PUBLIC ./Textractor/include/common.h)

add_library(pch ./Textractor/text.cpp)
target_precompile_headers(pch PUBLIC ./Textractor/include/common.h)

add_subdirectory(./Textractor/host)
target_link_libraries(hookcli pch)
target_link_libraries(hookcli host)