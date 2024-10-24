#include "RenderWindow.h"
#include "ReVengine.h"
#include "SDL.h"
#include "d3d11.h"
#include "Direct3D11/WindowHandler.h"
#include <memory>

using namespace RevDev;

RenderWindow::RenderWindow(int windowWidth, int windowHeight) : 
    width{ windowWidth }, 
    height{ windowHeight }
{
}

RenderWindow::~RenderWindow()
{
}

bool RenderWindow::InitWindow() {

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        //Create window
        window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow("WINDOW OF GODS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow
        );
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        //Get window surface
        screenSurface = SDL_GetWindowSurface(window.get());

        //Fill the surface white
        //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        //Update the surface
        //SDL_UpdateWindowSurface(window);

        creatorGod = std::make_unique<D3D11Creator>(window.get(), width, height);
        creatorGod->setupDeviceAndSwap();

        LoopWindow();
        return true;
    }
    return false;
}

int RenderWindow::LoopWindow()
{
    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        //Main Game Loop
        //mainLoop();
        creatorGod->updateWindow();
    }

    //Destroy window
    SDL_DestroyWindow(window.get());

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}