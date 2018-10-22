cmake_minimum_required(VERSION 3.8)
project(heatDiffusion)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)
include_directories(grid)
include_directories(plot)
set(SOURCE_FILES main.cpp grid/grid.cpp plot/plot.cpp grid/grid_cell.cpp
         grid/grid_surf.cpp )
add_executable(heatDiffusion ${SOURCE_FILES})