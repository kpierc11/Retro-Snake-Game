#include "game.hpp"
#include <cmath>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

float m_moveTimer = 0.0f;
float m_moveDelay = 0.0625f;

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_screenWidth(900), m_screenHeight(480), m_gameScoreCount(0), m_cellSize(20), m_gameRunning(true), m_currentFrameTime(SDL_GetTicks()), m_previousFrameTime(0), m_grid({}), m_snake({this})
{
}

Game::~Game()
{
}

bool Game::InitGame()
{
    // Initialize sdl3
    SDL_Init(SDL_INIT_VIDEO);

    m_window = SDL_CreateWindow(
        "Retro Snake Game",
        m_screenWidth,
        m_screenHeight,
        SDL_WINDOW_OPENGL);

    if (m_window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 0;
    }

    m_renderer = SDL_CreateRenderer(m_window, "");

    if (m_renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return 0;
    }

    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return 0;
    }

    // char *filePath = SDL_GetPrefPath("EmberwindStudios", "PongGame");

    // printf(filePath);
    // WriteGameFile();
    // ReadGameFile();

    // Create Snake
    int rows = m_screenHeight / m_cellSize;
    int columns = m_screenWidth / m_cellSize;

    m_grid.clear();
    m_grid.reserve(static_cast<size_t>(rows * columns));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {

            SDL_FRect rect{};
            rect.h = m_cellSize;
            rect.w = m_cellSize;
            rect.x = j * m_cellSize;
            rect.y = i * m_cellSize;

            m_grid.push_back(rect);
        }
    }

    int centerIndex = ((rows * columns) - 100);
    m_snake.m_snakeHead.x = m_grid[centerIndex].x;
    m_snake.m_snakeHead.y = m_grid[centerIndex].y;
    m_snake.m_currentSnakeGridPos = static_cast<int>(centerIndex);

    for (int i = 0; i < 2; i++)
    {
        SDL_FRect rect{};
        rect.h = m_snake.m_snakeSize;
        rect.w = m_snake.m_snakeSize;
        rect.x = (m_snake.m_snakeHead.x) + (m_snake.m_snakeSize * i);
        rect.y = m_snake.m_snakeHead.y;
        m_snake.m_snakeBody.push_back(rect);
    }

    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        int randomNum = rand() % m_screenWidth;

        int snakeFoodIndex = ((rows * columns) - randomNum);
        SDL_FRect food{};
        food.h = m_snake.m_snakeSize;
        food.w = m_snake.m_snakeSize;
        food.x = (m_grid[snakeFoodIndex].x);
        food.y = (m_grid[snakeFoodIndex].y);

        m_snake.m_snakeFood.push_back(food);
    }

    return 1;
}

void Game::EndGame()
{
    WriteGameFile();
    ReadGameFile();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    SDL_Quit();
}

void Game::GameLoop()
{

    while (m_gameRunning)
    {

        m_currentFrameTime = SDL_GetTicks();
        float deltaTime = (m_currentFrameTime - m_previousFrameTime) / 1000.0f;

        m_previousFrameTime = m_currentFrameTime;

        HandleInput();
        UpdateGame(deltaTime);
        GenerateOutput();
    }
}

void Game::HandleInput()
{

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_gameRunning = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            SDL_Keycode key = event.key.key;

            switch (key)
            {
            case SDLK_W:
                if (m_snake.m_currentDirection != Direction::South)
                    m_snake.m_currentDirection = Direction::North;
                break;

            case SDLK_S:
                if (m_snake.m_currentDirection != Direction::North)
                    m_snake.m_currentDirection = Direction::South;
                break;

            case SDLK_A:
                if (m_snake.m_currentDirection != Direction::East)
                    m_snake.m_currentDirection = Direction::West;
                break;

            case SDLK_D:
                if (m_snake.m_currentDirection != Direction::West)
                    m_snake.m_currentDirection = Direction::East;
                break;

            default:
                break;
            }
        }
    }
}

void Game::UpdateGame(float deltaTime)
{

    m_moveTimer += deltaTime;

    if (m_moveTimer >= m_moveDelay)
    {
        m_snake.Update(deltaTime);
        m_moveTimer = 0.0f;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(m_renderer, 50, 169, 86, 255);
    SDL_RenderClear(m_renderer);
    m_snake.Draw();

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    // render grid
    // for (auto &gridItem : m_grid)
    // {
    //     SDL_RenderRect(m_renderer, &gridItem);
    // }

    SDL_RenderPresent(m_renderer);
}

void Game::ReadGameFile()
{
    SDL_Storage *user = SDL_OpenUserStorage("EmberwindStudios", "PongGame", 0);
    if (user == NULL)
    {
    }
    while (!SDL_StorageReady(user))
    {
        SDL_Delay(1);
    }

    Uint64 saveLen = 0;
    if (SDL_GetStorageFileSize(user, "save0.sav", &saveLen) && saveLen > 0)
    {
        void *dst = SDL_malloc(saveLen);
        if (SDL_ReadStorageFile(user, "save0.sav", dst, saveLen))
        {
            // Interpret the bytes as an int
            int loadedScore = *(int *)dst;

            SDL_Log("Loaded score: %d", loadedScore);
        }
        else
        {
        }
        SDL_free(dst);
    }
    else
    {
    }

    SDL_CloseStorage(user);
}

void Game::WriteGameFile()
{

    SDL_Storage *user = SDL_OpenUserStorage("EmberwindStudios", "PongGame", 0);
    if (user == NULL)
    {
        SDL_Log("Couldn't open user storage: %s\n", SDL_GetError());
    }
    while (!SDL_StorageReady(user))
    {
        SDL_Delay(1);
    }

    int saveData = m_gameScoreCount;
    const void *saveDataPtr = &saveData;
    Uint64 saveLen = sizeof(saveData);
    if (!SDL_WriteStorageFile(user, "save0.sav", saveDataPtr, saveLen))
    {
    }

    SDL_CloseStorage(user);
}
