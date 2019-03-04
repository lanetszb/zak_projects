#include <cmath>
#include <vector>

#include <grid/grid.h>
#include <grid/gridSurface.h>


void processSurface(Grid &grid) {

    processSurfaceLeft(grid);
    processSurfaceRight(grid);

    processSurfaceTop(grid);
    processSurfaceBottom(grid);


    processSurfaceRightX(grid);
    processSurfaceRightY(grid);

    processSurfaceLeftX(grid);
    processSurfaceLeftY(grid);

    processSurfaceTopX(grid);
    processSurfaceTopY(grid);

    processSurfaceBottomX(grid);
    processSurfaceBottomY(grid);

}


void processSurfaceLeft(Grid &grid) {


    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesY[indCur] - grid.nodesY[indCur + grid.nX]);
            grid.surfaceLeft.push_back(value);

        }
}

void processSurfaceRight(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 1; j < grid.nX; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesY[indCur] - grid.nodesY[indCur + grid.nX]);
            grid.surfaceRight.push_back(value);

        }
}

void processSurfaceTop(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grid.nY; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesX[indCur] - grid.nodesX[indCur + 1]);
            grid.surfaceTop.push_back(value);

        }
}

void processSurfaceBottom(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = fabs(grid.nodesX[indCur] - grid.nodesX[indCur + 1]);
            grid.surfaceBottom.push_back(value);

        }
}

void processSurfaceRightX(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 1; j < grid.nX; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesX[indCur] + grid.nodesX[indCur + grid.nX]) / 2.;
            grid.surfaceRightX.push_back(value);

        }
}

void processSurfaceRightY(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 1; j < grid.nX; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesY[indCur] + grid.nodesY[indCur + grid.nX]) / 2.;
            grid.surfaceRightY.push_back(value);

        }
}

void processSurfaceLeftX(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesX[indCur] + grid.nodesX[indCur + grid.nX]) / 2.;
            grid.surfaceLeftX.push_back(value);

        }
}

void processSurfaceLeftY(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesY[indCur] + grid.nodesY[indCur + grid.nX]) / 2.;
            grid.surfaceLeftY.push_back(value);

        }
}

void processSurfaceTopX(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grid.nY; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesX[indCur] + grid.nodesX[indCur + 1]) / 2.;
            grid.surfaceTopX.push_back(value);

        }
}


void processSurfaceTopY(Grid &grid) {

    double value = 0;
    int indCur = 0;

    for (int i = 1; i < grid.nY; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesY[indCur] + grid.nodesY[indCur + 1]) / 2.;
            grid.surfaceTopY.push_back(value);

        }
}

void processSurfaceBottomX(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesX[indCur] + grid.nodesX[indCur + 1]) / 2.;
            grid.surfaceBottomX.push_back(value);

        }
}

void processSurfaceBottomY(Grid &grid) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grid.nY - 1; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            indCur = i * grid.nX + j;
            value = (grid.nodesY[indCur] + grid.nodesY[indCur + 1]) / 2.;
            grid.surfaceBottomY.push_back(value);

        }
}
