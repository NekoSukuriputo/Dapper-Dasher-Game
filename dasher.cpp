#include "raylib.h"

int main()
{
    // window dimentions
    const int windowWidth{512};
    const int windowHeight{380};

    // init window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to grafity (pixels/s)/s
    const int gravity{1'000};

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

    // nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    // nebula velocity
    int nebVel{-200};

    // animation frame
    int frame{};
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    // nebula anim
    int nebFrame{};
    const float nebUpdateTime(1.0 / 12.0);
    float nebRunningTime{};

    // is ractacle in the air
    bool isInAir{};
    // jump velocity {pixel/s}
    const int jumpVel{-600};

    int velocity{0};

    // set fps
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // delta time {time since last frame}
        const float dT{GetFrameTime()};

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
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebulaPos.x += nebVel * dT;
        // update the position
        scarfyPos.y += velocity * dT;

        // update scary animation frame

        if (!isInAir)
        {
            // update running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0;
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;

            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}