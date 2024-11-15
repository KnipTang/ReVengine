#include "RenderWindow.h"
#include "ReVengine.h"
#include "SDL.h"
#include "d3d11.h"
#include "Direct3D11/WindowHandler.h"
#include <memory>
#include "Utils/Vertex.h"
#include <algorithm>
#undef min
#undef max

using namespace RevDev;

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
    m_CreatorGod.reset();
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
        m_WindowWidth = windowWidth;
        m_WindowHeight = windowHeight;

        //Create window
        m_Window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow("WINDOW OF GODS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow
        );
        if (m_Window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        {
            m_CreatorGod = std::make_unique<WindowHandler_D3D11>(m_Window.get(), m_WindowWidth, m_WindowHeight);
            m_CreatorGod->Setup();
        }

        return true;
    }
}

void RevDev::RenderWindow::DrawMesh(uint32_t meshId)
{
    DirectX::XMMATRIX transformBuffer =
    {
            DirectX::XMMatrixTranspose
            (
                DirectX::XMMatrixRotationX(3.14f) *
                //DirectX::XMMatrixTranslation(0, 0, 5.f) *
                DirectX::XMMatrixPerspectiveLH(
                    1.f, 
                    std::min(float(m_WindowWidth), float(m_WindowHeight)) / std::max(float(m_WindowWidth), float(m_WindowHeight)),
                    0.5f,
                    10.f
                )
            )
    };

    m_CreatorGod->DrawMesh(meshId, transformBuffer);
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
    
    m_CreatorGod->updateWindow();

    return false;
}

void RevDev::RenderWindow::AddMesh(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices)
{
    m_CreatorGod->AddMesh(vertices, indices);
}

void RevDev::RenderWindow::RipWindow()
{
    //Destroy window
    SDL_DestroyWindow(m_Window.get());

    //Quit SDL subsystems
    SDL_Quit();
}
