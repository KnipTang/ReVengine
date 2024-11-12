#include "RenderWindow.h"
#include "ReVengine.h"
#include "SDL.h"
#include "d3d11.h"
#include "Direct3D11/WindowHandler.h"
#include <memory>

using namespace RevDev;

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
    creatorGod.reset();
}

bool RenderWindow::InitWindow(int windowWidth, int windowHeight) {
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
            SDL_CreateWindow("WINDOW OF GODS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow
        );
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        {
            creatorGod = std::make_unique<WindowHandler_D3D11>(window.get(), windowWidth, windowHeight);
            creatorGod->setupDeviceAndSwap();
        }

        return true;
    }
}

void RevDev::RenderWindow::DrawWindow()
{
    creatorGod->drawWindow();
}

bool RenderWindow::UpdateWindow()
{
    //To get window to stay up
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return true;

    }    
    
    creatorGod->updateWindow();

    return false;
}

void RevDev::RenderWindow::RipWindow()
{
    //Destroy window
    SDL_DestroyWindow(window.get());

    //Quit SDL subsystems
    SDL_Quit();
}
