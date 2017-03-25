cmake_minimum_required(VERSION 3.5)
project(NaSt2D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



set(SOURCE_FILES
    source/boundary.c
    source/boundary.h
    source/datadef.h
    source/init.c
    source/init.h
    source/main.c
    source/surface.c
    source/surface.h
    source/uvp.c
    source/uvp.h
    source/visual.c
    source/visual.h)

add_executable(NaSt2D ${SOURCE_FILES})