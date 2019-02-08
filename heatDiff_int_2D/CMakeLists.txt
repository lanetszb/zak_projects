cmake_minimum_required(VERSION 3.8)
project(heatDiff_int_2D)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)

set(SOURCE_FILES

        main.cpp

        plot/plot.cpp

        grid/gridCell.cpp grid/gridSurf.cpp grid/grid.cpp

        matrix/matrix.cpp matrix/matrixCoeff.cpp matrix/matrixVect.cpp

        param/param.cpp

        extra/computeProperties.cpp
        extra/readProperties.cpp extra/readProperties.h extra/jacobi.cpp)

add_executable(heatDiff_int_2D ${SOURCE_FILES})