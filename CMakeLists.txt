cmake_minimum_required(VERSION 3.3)
project(completed)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        cs2123p5.h
        cs2123p5DM.c
        cs2123p5Driver.c
        cs2123p5GG.c
        cs2123p5JM.c
        cs2123p5QQ.c)

add_executable(completed ${SOURCE_FILES})