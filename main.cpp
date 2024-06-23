// Using the raylib libaries
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"
#include <string>

// Main Function
int main()
{
    // Define Window Dimensions
    int windowDimension[2];
    windowDimension[0] = 384;
    windowDimension[1] = 384;

    // Initalize Window
    InitWindow(windowDimension[0], windowDimension[1], "Classy Clash");

    // Load Texture Map
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale {4.f};

    //Creating a knight instance
    Character knight{windowDimension[0],windowDimension[1]};
    
    //Draw the props
    Prop props[2]
    {
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    //Draw Enemy
    Enemy goblin{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"),LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy* enemies[]
    {
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        enemy ->setTarget(&knight);
    }

    // Definition of the FPS this Game will have
    SetTargetFPS(60);

    // Game Loop
    while (WindowShouldClose() == false)
    {
        // Begin Drawing
        BeginDrawing();
        // Begin Game Logic
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // Draw Map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        //Rock Position
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive())
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        //Calling Tick Function
        knight.tick(GetFrameTime());
        
        //Calling Enemy Tick
        for(auto enemy : enemies)
        {
            enemy ->tick(GetFrameTime());
        }
        
        //Check Position of the player in relation to the map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            (knight.getWorldPos().x + (float)windowDimension[0]) > (map.width * mapScale) ||
            (knight.getWorldPos().y + (float)windowDimension[1]) > (map.height * mapScale))
        {
            knight.undoMovement();
        }
        //Check collision with a prop

    for(auto prop : props)
    {
        if(CheckCollisionRecs(knight.getCollisionRec(),prop.getCollisionRec(knight.getWorldPos())))
        {
            knight.undoMovement();
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for(auto enemy : enemies)
        {
            if(CheckCollisionRecs(enemy->getCollisionRec(),knight.getWeaponCollisionRec()))
            {
                enemy->setAlive(false);
            }
        }
    }
        
        // End Drawing
        EndDrawing();
    }
    CloseWindow();
}
