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
        if (m_snakeHead.x == m_snakeBody[i].x && m_snakeHead.y == m_snakeBody[i].y)
        {
            std::cout << "Snake head hit the body!" << "\n";
            // SDL_RenderDebugText(m_game->m_renderer, static_cast<float>(m_game->m_screenWidth / 2), 10, "Game Over!!");
            // m_game->m_gameRunning = false;
        }

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

    for (auto &food : m_snakeFood)
    {
        if (m_snakeHead.x == food.x && m_snakeHead.y == food.y)
        {
            m_snakeBody.push_back(food);
        }
    }
}

void Snake::Draw()
{
    SDL_SetRenderDrawColor(m_game->GetRenderer(), 25, 25, 112, 255);

    SDL_RenderFillRect(m_game->GetRenderer(), &m_snakeHead);

    SDL_SetRenderDrawColor(m_game->GetRenderer(), 135, 206, 250, 255);

    // std::cout << m_snakeBody.size() << "\n";
    for (auto &snakeBody : m_snakeBody)
    {
        SDL_RenderFillRect(m_game->GetRenderer(), &snakeBody);
    }

    SDL_SetRenderDrawColor(m_game->GetRenderer(), 128, 0, 32, 255);

    for (auto &food : m_snakeFood)
    {
        SDL_RenderFillRect(m_game->GetRenderer(), &food); 
    }
}

// void Snake::AddPivotPoint(Direction direction, int pivotPosition)
// {
//     PivotPoint pivot{};
//     pivot.currentDirection = direction;
//     pivot.pivotPos = pivotPosition;

//     m_pivotPoints.push_back(pivot);
// }
