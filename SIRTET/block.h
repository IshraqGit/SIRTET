#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using namespace std;

class Block
{
public : 
    Block();
    void Draw(int offset_x, int offset_y, bool reverse);
    void Move(int rows, int columns);
    vector<Position> getCellPositions();
    int id;
    map < int,vector<Position> > cells;
    void Rotate();
    void UndoRotation();

private:
    int row_offset;
    int column_offset;
    int cellSize;
    int rotationState;
    vector<Color> colors;
};