#include "RenderWindow.h"
#include "ReVengine.h"
#include "SDL.h"
#include "d3d11.h"
#include "Direct3D11/WindowHandler.h"
#include <memory>
#include "Utils/Vertex.h"
#include <algorithm>
#include "Texture.h"
#include "Rendering/Direct3D11/Mesh.h"
#include "Rendering/Direct3D11/TextureShader.h"
#include <Rev_CoreSystems.h>

#undef min
#undef max

using namespace RevDev;

RenderWindow::RenderWindow()
{
    m_VertexStride = sizeof(Vertex);
}

RenderWindow::~RenderWindow()
{
    m_CreatorGod.reset();
}

bool RenderWindow::InitWindow(int windowWidth, int windowHeight, float nearZ, float farZ) {
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

        m_ProjectionMatrix = DirectX::XMMatrixPerspectiveLH(
            1.f,
            std::min(float(m_WindowWidth), float(m_WindowHeight)) / std::max(float(m_WindowWidth), float(m_WindowHeight)),
            nearZ,
            farZ
        );
        m_WorldMatrix = DirectX::XMMatrixIdentity();

        //Create window
        m_Window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
            SDL_CreateWindow("WINDOW OF GODS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow
        );

        if (m_Window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        //SDL_WarpMouseInWindow(m_Window.get(), m_WindowWidth / 2, m_WindowHeight / 2);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        //SDL_ShowCursor(SDL_ENABLE);

        {
            m_CreatorGod = std::make_unique<WindowHandler_D3D11>(m_Window.get(), m_WindowWidth, m_WindowHeight);
            m_CreatorGod->Setup();
        }

        return true;
    }
}

uint32_t RevDev::RenderWindow::AddMesh(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices, Rev::Texture* texture)
{
    TextureShader* textureShader = new TextureShader{ m_CreatorGod->GetDevice(), m_CreatorGod->GetDeviceContext(), texture };

    m_Meshes.emplace_back(std::make_unique<Mesh>(m_CreatorGod->GetDevice(), textureShader));

    m_Meshes.back()->setupVertexBuffer(vertices);
    m_Meshes.back()->setupIndexBuffer(indices);

    return m_Meshes.back()->GetID();
}

void RevDev::RenderWindow::DrawMesh(uint32_t meshId, const glm::mat4 worldMatrix, const DirectX::XMMATRIX viewMatrix)
{
    DirectX::XMMATRIX worldMatrixDirectX = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&worldMatrix));
    DirectX::XMMATRIX transWorld = DirectX::XMMatrixTranspose(worldMatrixDirectX);
    DirectX::XMMATRIX transView = DirectX::XMMatrixTranspose(viewMatrix);
    DirectX::XMMATRIX transProj = DirectX::XMMatrixTranspose(m_ProjectionMatrix);

    ID3D11DeviceContext* pDeviceContext = m_CreatorGod->GetDeviceContext();

    //Vertex buffer is a buffer that holds the vertex data
    auto&& mesh = m_Meshes.at(meshId);
    auto&& textureShader = mesh->GetTextureShader();
    wrl::ComPtr<ID3D11Buffer> matrixBuffer = textureShader->GetMatrixBuffer();

    pDeviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer().GetAddressOf(), &m_VertexStride, &m_VertexOffset);
    pDeviceContext->IASetIndexBuffer(mesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

    D3D11_MAPPED_SUBRESOURCE msr;
    pDeviceContext->Map(matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    MatrixBufferType* data = (MatrixBufferType*)msr.pData;
    data->world = transWorld;
    data->view = transView;
    data->projection = transProj;
   // memcpy(msr.pData, data, sizeof(DirectX::XMMATRIX));
    pDeviceContext->Unmap(matrixBuffer.Get(), 0);

    pDeviceContext->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

    textureShader->SetShader();

    pDeviceContext->DrawIndexed(mesh->GetIndiceCount(), 0, 0);
}

bool RenderWindow::UpdateWindow()
{
    //To get window to stay up
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            Rev::Rev_CoreSystems::pInputManager->HandleKeyDown(e.key.keysym.scancode);
            break;

        case SDL_QUIT:
                return true;
            break;
        }
    }    

    int xRel, yRel;
    SDL_GetRelativeMouseState(&xRel, &yRel);
    Rev::Rev_CoreSystems::pInputManager->HandleMouseRelativeMotion(xRel, yRel);

    m_CreatorGod->updateWindow();

    return false;
}

void RevDev::RenderWindow::RipWindow()
{
    //Destroy window
    SDL_DestroyWindow(m_Window.get());

    //Quit SDL subsystems
    SDL_Quit();
}
