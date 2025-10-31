
#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "snake.hpp"
#include "math.hpp"

class Game
{

public:
    Game();
    ~Game();

    bool InitGame();
    void GameLoop();
    void EndGame();
    SDL_Renderer *GetRenderer() { return m_renderer; }

    int m_screenWidth;
    int m_screenHeight;
    std::vector<SDL_FRect> m_grid;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_gameScoreCount;
    int m_cellSize;
    bool m_gameRunning;
    float m_speed;
    Uint64 m_currentFrameTime;
    Uint64 m_previousFrameTime;
    Snake m_snake;

private:
    void HandleInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    void ReadGameFile();
    void WriteGameFile();
};
