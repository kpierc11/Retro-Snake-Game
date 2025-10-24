#include "game.hpp"
#include <cmath>
#include <SDL3_ttf/SDL_ttf.h>

float scoreTimePassed = 0;

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_screenWidth(900), m_screenHeight(480), m_gameScoreCount(0), m_gameRunning(true), m_currentFrameTime(SDL_GetTicks()), m_previousFrameTime(0)
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
        SDL_WINDOW_OPENGL 
    );

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

    char *filePath = SDL_GetPrefPath("EmberwindStudios", "PongGame");

    printf(filePath);
    WriteGameFile();
    ReadGameFile();

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

        if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
           
        }
        if (event.type == SDL_EVENT_KEY_UP)
        {
        }
    }
}

void Game::UpdateGame(float deltaTime)
{
    float mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

}

void Game::GenerateOutput()
{

    SDL_SetRenderDrawColor(m_renderer, 12, 12, 12, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

    SDL_RenderPresent(m_renderer);
}

void Game::ReadGameFile()
{
    SDL_Storage *user = SDL_OpenUserStorage("EmberwindStudios", "PongGame", 0);
    if (user == NULL)
    {
        // Something bad happened!
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
            // Something bad happened!
        }
        SDL_free(dst);
    }
    else
    {
        // Something bad happened!
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
