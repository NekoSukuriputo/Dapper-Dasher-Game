#include "raylib.h"

int main()
{
    // window dimentions
    const int windowWidth{512};
    const int windowHeight{380};

    // init window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to grafity (pixels/frame)/frame
    const int gravity{1};

    // rectangle dimentions
    const int width{50};
    const int height{80};

    //is ractacle in the air
    bool isInAir{};
    //jump velocity
    const int jumpVel{-22};

    int posY{windowHeight - height};
    int velocity{0};

    // set fps
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
         // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update the position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        // stop drawing
        EndDrawing();

    }

    CloseWindow();
}