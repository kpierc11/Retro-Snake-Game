#include "snake.hpp"
#include "game.hpp"

GameMath::Vector prevSnakeHeadPos = {0.0f, 0.0f};
GameMath::Vector prevBodyPos = {0.0f, 0.0f};

Snake::Snake(Game *game) : GameObject(game), m_currentDirection(Direction::West)
{
    m_transform.x = 100;
    m_transform.y = 100;
    m_snakeSize = 20.0f;
    m_snakeHead.h = m_snakeSize;
    m_snakeHead.w = m_snakeSize;
}

Snake::~Snake()
{
}

void Snake::Update(float deltaTime)
{
    if (m_currentDirection == Direction::North)
    {
        prevSnakeHeadPos.y = m_snakeHead.y;
        prevSnakeHeadPos.x = m_snakeHead.x;
        if (m_currentSnakeGridPos - 45 < m_game->m_grid.size())
        {
            m_snakeHead.y = m_game->m_grid[m_currentSnakeGridPos - 45].y;
            m_currentSnakeGridPos = m_currentSnakeGridPos - 45;
        }
    }
    else if (m_currentDirection == Direction::South)
    {
        prevSnakeHeadPos.y = m_snakeHead.y;
        prevSnakeHeadPos.x = m_snakeHead.x;
        if (m_currentSnakeGridPos + 45 < m_game->m_grid.size())
        {
            m_snakeHead.y = m_game->m_grid[m_currentSnakeGridPos + 45].y;
            m_currentSnakeGridPos = m_currentSnakeGridPos + 45;
        }
    }
    else if (m_currentDirection == Direction::West)
    {
        prevSnakeHeadPos.y = m_snakeHead.y;
        prevSnakeHeadPos.x = m_snakeHead.x;
        if (m_currentSnakeGridPos - 1 < m_game->m_grid.size())
        {
            m_snakeHead.x = m_game->m_grid[m_currentSnakeGridPos - 1].x;
            m_currentSnakeGridPos = m_currentSnakeGridPos - 1;
        }
    }
    else if (m_currentDirection == Direction::East)
    {
        prevSnakeHeadPos.y = m_snakeHead.y;
        prevSnakeHeadPos.x = m_snakeHead.x;
        if (m_currentSnakeGridPos + 1 < m_game->m_grid.size())
        {
            m_snakeHead.x = m_game->m_grid[m_currentSnakeGridPos + 1].x;
            m_currentSnakeGridPos = m_currentSnakeGridPos + 1;
        }
    }

    for (int i = m_snakeBody.size() - 1; i >= 0; i--)
    {

        // // Store the first body x and y so we can make the next body item equal to these values.
        // prevBodyPos.x = m_snakeBody[0].x;
        // prevBodyPos.y = m_snakeBody[0].y;

        std::cout << i << "\n";

        // // Set the first body item to the previous snake head position.
        // m_snakeBody[i].x = prevSnakeHeadPos.x;
        // m_snakeBody[i].y = prevSnakeHeadPos.y;
        // Set

        if (i == 0)
        {
            m_snakeBody[i].x = prevSnakeHeadPos.x;
            m_snakeBody[i].y = prevSnakeHeadPos.y;
        }
        else
        {
            m_snakeBody[i].x = m_snakeBody[i - 1].x;
            m_snakeBody[i].y = m_snakeBody[i - 1].y;
        }
    }
}

void Snake::Draw()
{
    SDL_RenderFillRect(m_game->GetRenderer(), &m_snakeHead);

    // std::cout << m_snakeBody.size() << "\n";
    for (auto &snakeBody : m_snakeBody)
    {
        SDL_RenderFillRect(m_game->GetRenderer(), &snakeBody);
    }
}

void Snake::AddPivotPoint(Direction direction, int pivotPosition)
{
    PivotPoint pivot{};
    pivot.currentDirection = direction;
    pivot.pivotPos = pivotPosition;

    m_pivotPoints.push_back(pivot);
}
