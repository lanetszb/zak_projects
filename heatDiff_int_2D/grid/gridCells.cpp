#include <cmath>

#include <grid/grid.h>
#include <grid/gridCells.h>


void processCells(Grid &grid){    

    processCellsX(grid);
    processCellsY(grid);

    processCellsVolume(grid);

    processLLeft(grid);
    processLRight(grid);
    processLTop(grid);
    processLBottom(grid);
    
}


void processCellsX(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesX[indCur] + grid.nodesX[indCur + 1] +
                         grid.nodesX[indCur + grid.nX] +
                         grid.nodesX[indCur + 1 + grid.nX]) / 4;

            grid.cellsX.push_back(value);

        }
}

void processCellsY(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesY[indCur] + grid.nodesY[indCur + 1] +
                         grid.nodesY[indCur + grid.nX] +
                         grid.nodesY[indCur + 1 + grid.nX]) / 4;

            grid.cellsY.push_back(value);

        }
}

void processCellsVolume(Grid &grid) {

    std::vector<double> semiPerimeter(grid.nCells, 0);

    double value = 0;

    for (int i = 0; i < semiPerimeter.size(); i++)
        semiPerimeter[i] =
                (grid.surfaceRight[i] + grid.surfaceLeft[i] + grid.surfaceTop[i] +
                 grid.surfaceBottom[i]) / 2;

    std::vector<double> gridArea(grid.nCells, 0);

    for (int i = 0; i < gridArea.size(); i++)
        gridArea[i] = sqrt((semiPerimeter[i] - grid.surfaceRight[i]) *
                           (semiPerimeter[i] - grid.surfaceLeft[i]) *
                           (semiPerimeter[i] - grid.surfaceTop[i]) *
                           (semiPerimeter[i] - grid.surfaceBottom[i]));

    // Grid volume

    std::vector<double> gridZheight(grid.nCells, 1);

    for (int i = 0; i < gridArea.size(); i++) {
        value = gridArea[i] * gridZheight[i];
        grid.cellsVolume.push_back(value);
    }
}

void processLLeft(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 1; j < grid.nX - 1; j++) {

            indCur = i * (grid.nX - 1) + j;
            value = fabs(
                    grid.cellsX[indCur] - grid.cellsX[indCur - 1]);

            grid.LLeft.push_back(value);

        }
}

void processLRight(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 2; j++) {

            indCur = i * (grid.nX - 1) + j;
            value = fabs(
                    grid.cellsX[indCur] - grid.cellsX[indCur + 1]);

            grid.LRight.push_back(value);

        }
}

void processLTop(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 2; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * (grid.nX - 1) + j;
            value = fabs(
                    grid.cellsY[indCur] - grid.cellsY[indCur + (grid.nX - 1)]);

            grid.LTop.push_back(value);

        }
}

void processLBottom(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * (grid.nX - 1) + j;
            value = fabs(
                    grid.cellsY[indCur] - grid.cellsY[indCur - (grid.nX - 1)]);

            grid.LBottom.push_back(value);

        }
}