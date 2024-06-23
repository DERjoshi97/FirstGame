#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

// create class Character
class Character : public baseCharacter
{
public:
    virtual void tick(float deltaTime) override;
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec()
    {
        return weaponCollisonRec;
    }
    float getHealth() const
    {
        return health;
    }
    void takeDamage(float damage);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisonRec{};
    float health{100.f};

};
#endif