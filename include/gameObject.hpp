#pragma once
#include "math.hpp"
#include <SDL3/SDL.h>

class GameObject
{
public:
    GameObject(class Game *game);
    ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw();

    GameMath::Vector m_transform;
    float m_scale;
    float m_rotation;
    class Game *m_game;
};