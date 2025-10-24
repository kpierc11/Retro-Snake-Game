#include "game.hpp"

int main()
{

    Game game;

    bool gameInit = game.InitGame();

    if (gameInit)
    {
        game.GameLoop();
    }

    game.EndGame();

    return 0;
}