#include <SDL3/SDL_main.h>

#include "GameEngine.h"
#include "SpaceInvadersGame.h"


int main(int argc, char* argv[])
{
    SpaceInvaders::SpaceInvadersGame game;
    if (!game.Init("Space Invaders", 1600, 900))
    {
        return -1;
    }

    game.Run();
    return 0;
}
