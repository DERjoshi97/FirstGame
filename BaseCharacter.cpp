#include "BaseCharacter.h"
#include "raymath.h"

baseCharacter::baseCharacter()
{

};
void baseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle baseCharacter::getCollisionRec()
{
    return Rectangle
    {
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}
void baseCharacter::tick(float deltaTime)
{
    //setting WorldPos to WorldPosLastFrame to undo the character movement
    worldPosLastFrame = worldPos;
    // Update Animation Frame
    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
        // check Vector Direction an perform movement

    if (Vector2Length(Velocity) != 0.0)
    {
        // set worldPos = worldPos + direction (nomrmalized)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(Velocity), speed));
        // Check the current Direction the knight is facing
        if (Velocity.x < 0.f)
        {
            rightLeft = -1.f;
        }
        else
        {
            rightLeft = 1.f;
        }
        texture = run;
    }
    else
    {
        texture = idle;
    }
    Velocity = {};
    // DrawKnight
    Rectangle source{frame * width,0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}