#include <iostream>
#include <iostream>
#include "src/raylib.h"
#include "Game.h"
#include "colors.h"

using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    // creating a game window
    InitWindow(500, 620, "Sirtet");
    // setting the frames per second
    SetTargetFPS(60);

    // creating a grid objects
    Grid grid;
    // grid.grid[0][0] = 1;
    // grid.grid[3][9] = 4;
    // grid.grid[0][1] = 6;
    // grid.grid[17][8] = 7;
    grid.Print();

    Font font = LoadFontEx("resources/arial.ttf", 64, 0, 0); // text font

    Game game = Game();

    IBlock block = IBlock();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();

        if (EventTriggered(0.5))
        {
            game.MoveBlockDown();
        }
        // setting up the background color
        ClearBackground(darkBlue);
        BeginDrawing();
        DrawTextEx(font, "Score", {350, 15}, 37, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 30, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font , scoreText , 38 , 2);

        DrawTextEx(font , scoreText,{305+(170-textSize.x)/2,66},38 , 2 , WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();

        EndDrawing();
    }
    // closing the game window
    CloseWindow();
}