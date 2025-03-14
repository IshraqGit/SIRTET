#include "Game.h"
#include <random>
#include <fstream>

using namespace std;

Game ::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}
Game ::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}
Block Game ::GetRandomBlock()
{
    if (blocks.empty())
        blocks = GetAllBlocks();
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game ::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game ::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11, true);

    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290, false);
        break;
    case 4:
        nextBlock.Draw(255, 275, false);
        break;
    default:
        nextBlock.Draw(270, 270, false);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_UP:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        RotateBlock();
        break;
    }
}

void Game ::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutSide() || BlockFits() == false)
            currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutSide() || BlockFits() == false)
            currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutSide() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutSide()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutSide(item.row, item.column))
            return true;
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if (IsBlockOutSide() || BlockFits() == false)
        currentBlock.UndoRotation();
    else
        PlaySound(rotateSound);
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (grid.isCellEmpty(item.row, item.column) == false)
            return false;
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void updateFileData(int newScore) {
    int oldScore;
    ifstream infile("score.dat");
    infile >> oldScore;
    infile.close();

    newScore = max(newScore, oldScore);
    ofstream ofile("score.dat");
    ofile << newScore << endl;
    ofile.close();
}

void Game ::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 200;
        break;
    case 3:
        score += 300;
        break;
    default:
        break;
    }
    score += moveDownPoints;
    updateFileData(score);
}
