cmake_minimum_required(VERSION 3.8)
project(heatDiff_int_2D)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)

include_directories(../colorconsole)
include_directories(/usr/local/include)

set(SOURCE_FILES

        main.cpp

        plot/plot.cpp

        grid/gridCells.cpp grid/gridSurface.cpp grid/grid.cpp

        matrix/matrix.cpp

        settings/settings.cpp

        extra/computeTInitial.cpp extra/computeTInitial.h extra/jacobi.cpp

        properties/propertyTables.cpp properties/properties.cpp

        coefficients/coefficients.cpp)

add_executable(heatDiff_int_2D ${SOURCE_FILES})
add_executable(progressbar main.cpp)