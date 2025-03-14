#include "block.h"

Block :: Block()
{
    cellSize = 30 ;
    rotationState = 0;
    colors = getCellColors();
    row_offset = 0;
    column_offset = 0;
}

void Block :: Draw(int offset_x , int offset_y, bool reverse)
{
    vector<Position> tiles = getCellPositions();
    for(Position tile : tiles)
    {
        Color cellColor = colors[id];
        int row;
        if(reverse)
            row = 20 - tile.row - 1;
        else
            row = tile.row;
        DrawRectangle(tile.column * cellSize+offset_x , row * cellSize+offset_y , cellSize-1 , cellSize-1 , cellColor);
    }
}

void Block :: Move(int rows , int columns)
{
    row_offset += rows;
    column_offset += columns;
}

vector<Position> Block :: getCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for(Position item : tiles)
    {
        Position newPos = Position(item.row + row_offset , item.column + column_offset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState++;
    if(rotationState ==(int)cells.size()) rotationState = 0;
}

void Block::UndoRotation()
{
    rotationState--;
    if(rotationState == -1) rotationState = cells.size()-1;
}
