#include <SDL3/SDL_main.h>
#include "Game/Game.h"

int main(int argc, char* argv[])
{
    Game game;
    if(!game.Init("Death Run", 1920, 1080))
    {
        return -1;
    }

    game.Run();
    return 0;
}
