#include <SDL3/SDL_main.h>

#include "GameEngine.h"

int main(int argc, char* argv[])
{
    GameEngine engine;
    if(!engine.Init("Death Run", 1920, 1080))
    {
        return -1;
    }

    engine.Run();
    return 0;
}
