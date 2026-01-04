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
    m_snakeHeadAngle = 180.0;
    m_headTexture = nullptr;
    m_bodyTexture = nullptr;
    m_foodTexture = nullptr;
}

Snake::~Snake()
{
    SDL_DestroyTexture(m_headTexture);
    SDL_DestroyTexture(m_bodyTexture);
    SDL_DestroyTexture(m_foodTexture);
}

void Snake::Update(float deltaTime)
{

    //Set the previous snake head position for reference
    SetPrevSnakeHeadData({m_snakeHead.x, m_snakeHead.y}, m_snakeHeadAngle);

    //Check the current direction of the snake and adjust positioning for changing
    if (m_currentDirection == Direction::North)
    {
        std::cout << "current snake grid pos north: " <<  m_currentSnakeGridPos<< "\n";
        if (m_currentSnakeGridPos - m_game->m_columns < m_game->m_grid.size())
        {
            m_snakeHead.y = m_game->m_grid[m_currentSnakeGridPos - m_game->m_columns].y;
            m_currentSnakeGridPos = m_currentSnakeGridPos - m_game->m_columns;
        }
    }
    else if (m_currentDirection == Direction::South)
    {

        if (m_currentSnakeGridPos + m_game->m_columns < m_game->m_columns * m_game->m_rows)
        {
            m_snakeHead.y = m_game->m_grid[m_currentSnakeGridPos + m_game->m_columns].y;
            m_currentSnakeGridPos = m_currentSnakeGridPos + m_game->m_columns;
        }
    }
    else if (m_currentDirection == Direction::West)
    {
        std::cout << "current snake grid pos west: " <<  m_currentSnakeGridPos<< "\n";
        std::cout << "Column Count: " <<  m_game->m_columns<< "\n";

        if (m_currentSnakeGridPos - 1 < m_game->m_grid.size() )
        {
            m_snakeHead.x = m_game->m_grid[m_currentSnakeGridPos - 1].x;
            m_currentSnakeGridPos = m_currentSnakeGridPos - 1 ;

        }
    }
    else if (m_currentDirection == Direction::East)
    {

        if (m_currentSnakeGridPos + 1 < m_game->m_columns)
        {
            m_snakeHead.x = m_game->m_grid[m_currentSnakeGridPos + 1].x;
            m_currentSnakeGridPos = m_currentSnakeGridPos + 1;
        }
    }

    for (int i = m_snakeBody.size() - 1; i >= 0; i--)
    {
        if (m_snakeHead.x == m_snakeBody[i].x && m_snakeHead.y == m_snakeBody[i].y)
        {
            // std::cout << "Snake head hit the body!" << "\n";
            m_game->m_gameRunning = false;
        }

        if (i == 0)
        {
            m_snakeBody[i].x = m_snakeHeadPreLoc.prevHeadLocData.x;
            m_snakeBody[i].y = m_snakeHeadPreLoc.prevHeadLocData.y;
        }
        else
        {
            m_snakeBody[i].x = m_snakeBody[i - 1].x;
            m_snakeBody[i].y = m_snakeBody[i - 1].y;
        }
    }

    for (auto &item : m_snakeFood)
    {
        if (m_snakeHead.x == item.food.x && m_snakeHead.y == item.food.y)
        {
            m_snakeBody.push_back(item.food);
            item.showFood = false;
        }
    }
}

void Snake::Draw()
{
    SDL_SetRenderDrawColor(m_game->GetRenderer(), 25, 25, 112, 255);

    SDL_RenderFillRect(m_game->GetRenderer(), &m_snakeHead);

    // SDL_RenderRotated(m_game->GetRenderer(),
    //                          m_headTexture,
    //                          nullptr,
    //                          &m_snakeHead,
    //                          m_snakeHeadAngle,
    //                          nullptr,
    //                          SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(m_game->GetRenderer(), 135, 206, 250, 255);

    for (auto &snakeBody : m_snakeBody)
    {
        // SDL_RenderTextureRotated(m_game->GetRenderer(),
        //                          m_bodyTexture,
        //                          nullptr,
        //                          &snakeBody,
        //                          m_snakeHeadPreLoc.rotAngle,
        //                          nullptr,
        //                          SDL_FLIP_NONE);
        SDL_RenderFillRect(m_game->m_renderer, &snakeBody);
    }

    SDL_SetRenderDrawColor(m_game->GetRenderer(), 128, 0, 32, 255);

    for (auto &item : m_snakeFood)
    {
        if (item.showFood)
        {
            SDL_RenderFillRect(m_game->GetRenderer(), &item.food);
        }
        // SDL_RenderTexture(m_game->GetRenderer(), m_foodTexture, NULL, &food);
    }
}

void Snake::SetPrevSnakeHeadData(GameMath::Vector prevLocation, double currentAngle)
{
    m_snakeHeadPreLoc.prevHeadLocData = prevLocation;
    m_snakeHeadPreLoc.rotAngle = currentAngle;
}
