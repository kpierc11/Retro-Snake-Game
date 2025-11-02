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

class Snake : GameObject
{

public:
    Snake(class Game *game);
    ~Snake();

    void Update(float deltaTime) override;
    void Draw() override;
    void AddPivotPoint(Direction direction, int pivotPosition);
    float m_snakeSize;
    int m_currentSnakeGridPos;
    int m_targetGridPos;
    Direction m_currentDirection;
    SDL_FRect m_snakeHead;  
    std::vector<SDL_FRect> m_snakeBody{};
    std::vector<SDL_FRect> m_snakeFood{};
};