cmake_minimum_required(VERSION 3.5)
project(NaSt2D_2_0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES
        "Program/boundary.c"
        "Program/boundary.h"
        "Program/datadef.h"
        "Program/flag.c"
        "Program/flag.h"
        "Program/init.c"
        "Program/init.h"
        "Program/main.c"
        "Program/surface.c"
        "Program/surface.h"
        "Program/turbulence.c"
        "Program/turbulence.h"
        "Program/uvp.c"
        "Program/uvp.h"
        "Program/visual.c"
        "Program/visual.h"
        "Program/zeit.gnu"
        )

add_executable(NaSt2D_2_0 ${SOURCE_FILES})