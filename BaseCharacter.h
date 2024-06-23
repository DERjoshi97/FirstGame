#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

//create base class

class baseCharacter
{
public:
    baseCharacter();
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    Rectangle getCollisionRec();
    void undoMovement();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive()
    {
        return alive;
    }
    void setAlive(bool isAlive)
    {
        alive = isAlive;
    }
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    /*Direction of the knight
    1: facing right,
    -1: facing Left
    */
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.f};
    Vector2 Velocity{};

private:
    bool alive{true};

};
#endif