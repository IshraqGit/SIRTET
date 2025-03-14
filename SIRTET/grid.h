#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Grid
{
public:
    Grid();
    void Initialize();
    void Draw();
    int grid[20][10];
    void Print();
    bool IsCellOutSide(int row, int col);
    bool isCellEmpty(int row, int col);
    int ClearFullRows();

private:
    int numRows;
    int numCols;
    int cellSize;
    vector<Color> colors ;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowsDown(int row , int rowNums);
};