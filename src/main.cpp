#include "game.hpp"
#include <crtdbg.h>

int main()
{
// #ifdef _DEBUG
//     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// #endif
// #ifdef _DEBUG
// _CrtSetBreakAlloc(2225);
// #endif


    Game game;

    if (game.InitGame())
    {
        game.GameLoop();
    }

    game.EndGame(); // free everything here

// #ifdef _DEBUG
//     _CrtDumpMemoryLeaks(); // check AFTER cleanup
// #endif

    return 0;
}
