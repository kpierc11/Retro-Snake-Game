#pragma once
#include "gameObject.hpp"
#include <vector>

enum class Direction
{
    North,
    South,
    East,
    West
};

struct PrevHeadLocData
{
    GameMath::Vector prevHeadLocData;
    double rotAngle;
};

struct SnakeFood {
    SDL_FRect food; 
    bool showFood;
};

class Snake : GameObject
{

public:
    Snake(class Game *game);
    ~Snake();

    void SetPrevSnakeHeadData(GameMath::Vector prevLocation, double currentAngle);

    void Update(float deltaTime) override;
    void Draw() override;
    float m_snakeSize;
    int m_currentSnakeGridPos;
    int m_targetGridPos;
    Direction m_currentDirection;
    SDL_FRect m_snakeHead;
    std::vector<SDL_FRect> m_snakeBody{};
    std::vector<SnakeFood> m_snakeFood{};
    SDL_Texture *m_headTexture;
    SDL_Texture *m_bodyTexture;
    SDL_Texture *m_foodTexture;
    double m_snakeHeadAngle;
    PrevHeadLocData m_snakeHeadPreLoc;
};