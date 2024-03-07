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

    // init scarfy sprite sheet
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // is ractacle in the air
    bool isInAir{};
    // jump velocity
    const int jumpVel{-22};

    int velocity{0};

    // set fps
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
}