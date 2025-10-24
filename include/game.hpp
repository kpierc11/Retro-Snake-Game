
#include <SDL3/SDL.h>
#include <iostream>


class Game
{

public:
    Game();
    ~Game();

    bool InitGame();
    void GameLoop();
    void EndGame();

    int m_screenWidth;
    int m_screenHeight;

private:
    void HandleInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    void ReadGameFile();
    void WriteGameFile();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_gameScoreCount;
    bool m_gameRunning;
    float m_speed;
    Uint64 m_currentFrameTime;
    Uint64 m_previousFrameTime;
 
};
