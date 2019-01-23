cmake_minimum_required(VERSION 3.8)
project(heatDiff_int_2D)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)

set(SOURCE_FILES

        main.cpp

        plot/plot.cpp

        grid/grid_cell.cpp grid/grid_surf.cpp grid/grid.cpp

        matrix/matrix.cpp matrix/matrix_coeff.cpp matrix/matrix_vect.cpp

        param.cpp

        random.cpp)

add_executable(heatDiff_int_2D ${SOURCE_FILES})