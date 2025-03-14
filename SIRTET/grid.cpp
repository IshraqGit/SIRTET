#include "grid.h"
#include <iostream>
#include "colors.h"

using namespace std;

Grid ::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = getCellColors();
}

void Grid :: Initialize()
{
    for(int row = 0 ; row < numRows ; row++)
    {
        for(int col = 0 ; col < numCols ; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid :: Print()
{
    for(int row = 0 ; row < numRows ; row++)
    {
        for(int col = 0 ; col < numCols ; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

bool Grid :: IsCellOutSide(int row , int col)
{
    if(row >= 0 && row < numRows && col >= 0 && col < numCols) return false;
    return true;
}

bool Grid::isCellEmpty(int row, int col)
{
    if(grid[row][col]== 0) return true;
    return false;
}

bool Grid :: IsRowFull(int row)
{
    for(int column = 0 ; column < numCols ; column++)
    {
        if(grid[row][column] == 0) return false;
    }
    return true;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows - 1 ; row >= 0 ; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if(completed > 0)
        {
            MoveRowsDown(row,completed);
        }
    }
    return completed;
}

void Grid :: ClearRow(int row)
{
    for(int col = 0 ; col < numCols ; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowsDown(int row, int rowNums)
{
    for(int col = 0 ; col < numCols ; col++)
    {
        grid[row+ rowNums][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

void Grid :: Draw()
{
    for(int row = 0 ; row < numRows ; row++)
    {
        for(int col = 0 ; col < numCols ; col++)
        {
            int cellValue = grid[numRows -row - 1][col];
            Color cellColor = colors[cellValue];
            DrawRectangle(col * cellSize+11 , row * cellSize+11 , cellSize-1 , cellSize-1 , cellColor);
        }
    }
}