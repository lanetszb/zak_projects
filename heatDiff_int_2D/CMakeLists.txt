cmake_minimum_required(VERSION 3.8)
project(heatDiff_int_2D)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)
include_directories(grid)
include_directories(plot)
set(SOURCE_FILES main.cpp plot/plot.cpp grid/grid_cell.cpp
         grid/grid_surf.cpp grid/grid.cpp grid/grid_struct.h)
add_executable(heatDiff_int_2D ${SOURCE_FILES})