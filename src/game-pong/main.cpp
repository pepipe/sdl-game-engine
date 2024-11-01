#include <SDL3/SDL_main.h>

#include "GameEngine.h"
#include "PongGame.h"

int main(int argc, char* argv[])
{
    PongGame game;
    if (!game.Init("Pong", 1600, 900))
    {
        return -1;
    }

    game.Run();
    return 0;
}
