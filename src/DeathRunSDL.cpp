#ifdef _WIN32
#include <Windows.h>
#endif

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

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    // Call main function
    return main(__argc, __argv);
}
#endif