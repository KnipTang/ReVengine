#include "Rendering/Direct3D11/WindowHandler.h"
#include <cassert>
#include "SDL.h"
#include <SDL_syswm.h>
#include "d3dcompiler.h"
#include <string>
#include "filesystem"
#include "fstream"
#include "DirectXMath.h"
#include "Utils/Vertex.h"
#include "Rendering/Mesh.h"

#pragma comment(lib, "d3d11.lib")

using namespace RevDev;

WindowHandler_D3D11::WindowHandler_D3D11(SDL_Window* window, int windowWidth, int windowHeight)
{
	SDL_SysWMinfo wmInfo{};
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	hwnd = wmInfo.info.win.window;

	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;

	m_VertexStride = sizeof(Vertex);
}

WindowHandler_D3D11::~WindowHandler_D3D11()
{

}

void RevDev::WindowHandler_D3D11::Setup()
{
	setupDeviceAndSwap();
	SetupRenderTargetAndStencelBuffer();

	compileShaders(m_VertexFile, m_PixelFile);
	SetupShaderBuffers();

	setupPipeline();
}

uint32_t WindowHandler_D3D11::AddMesh(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices)
{
	m_Meshes.emplace_back(std::make_unique<Mesh>(pDevice.Get()));
	m_Meshes.back()->setupVertexBuffer(vertices);
	m_Meshes.back()->setupIndexBuffer(indices);

	return m_Meshes.back()->GetID();
}

void WindowHandler_D3D11::DrawMesh(uint32_t index, const DirectX::XMMATRIX &transform)
{
	//Vertex buffer is a buffer that holds the vertex data
	auto&& mesh = m_Meshes.at(index);
	
	pDeviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer().GetAddressOf(), &m_VertexStride, &m_VertexOffset);
	pDeviceContext->IASetIndexBuffer(mesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

	D3D11_MAPPED_SUBRESOURCE msr;
	pDeviceContext->Map(pConstantBuffer.Get(), 0u,D3D11_MAP_WRITE_DISCARD, 0u,&msr);
	memcpy(msr.pData, &transform, sizeof(DirectX::XMMATRIX));
	pDeviceContext->Unmap(pConstantBuffer.Get(), 0u);

	pDeviceContext->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());

	pDeviceContext->DrawIndexed(mesh->GetIndiceCount(), 0, 0);
}

void WindowHandler_D3D11::updateWindow()
{
	pSwapChain->Present(1, 0);
	clearBuffer(m_BackgroundColour);
}

void WindowHandler_D3D11::clearBuffer(float backgroundColour[4])
{
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), backgroundColour);
	pDeviceContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH,1,0);
}

void WindowHandler_D3D11::setupPipeline()
{
	//Set type of rendering (point, line (strip), triangle (strip),.... Strip -> 0,1,2,3,4... Non-Strip = (0 - 1), (1 - 2), (5 - 0),...
	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Explain layout of vertices
	wrl::ComPtr<ID3D11InputLayout> inputLayer;
	const D3D11_INPUT_ELEMENT_DESC inputElement_DESC[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	pDevice->CreateInputLayout(inputElement_DESC, std::size(inputElement_DESC), m_VertexBytecode.c_str(), m_VertexBytecode.size(), &inputLayer);

	pDeviceContext->IASetInputLayout(inputLayer.Get());

	//Config viewport -> pixelshader target (renderTarget) From ndc to render view
	D3D11_VIEWPORT viewPort{};
	viewPort.Width = float(m_WindowWidth);
	viewPort.Height = float(m_WindowHeight);
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pDeviceContext->RSSetViewports(1, &viewPort);
}

void WindowHandler_D3D11::setupDeviceAndSwap()
{
	//Configure the desc(options) for the swapchain pointer
	DXGI_SWAP_CHAIN_DESC swapChainDESC = { 0 };
	ZeroMemory(&swapChainDESC, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDESC.BufferDesc.Width = 0;
	swapChainDESC.BufferDesc.Height = 0; //Width and height unspecified
	swapChainDESC.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDESC.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDESC.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDESC.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDESC.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDESC.SampleDesc.Count = 1;
	swapChainDESC.SampleDesc.Quality = 0; //Just means at this point no Anti Aliasing
	swapChainDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Use this buffer as render target
	swapChainDESC.BufferCount = 1; //one back buffer and one front
	swapChainDESC.OutputWindow = hwnd; //What window to output on
	swapChainDESC.Windowed = true;
	swapChainDESC.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDESC.Flags = 0;


	D3D_FEATURE_LEVEL feature_level;
	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//Creates swapchain, device and device context
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDESC,
		&pSwapChain,
		&pDevice,
		&feature_level,
		&pDeviceContext);
	assert(S_OK == hr && pSwapChain && pDevice && pDeviceContext);
}

void WindowHandler_D3D11::SetupRenderTargetAndStencelBuffer()
{
	HRESULT hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&pFramebuffer);
	assert(SUCCEEDED(hr));

	hr = pDevice->CreateRenderTargetView(
		pFramebuffer.Get(),
		nullptr,
		&pRenderTargetView);
	assert(SUCCEEDED(hr));

	//pFramebuffer->Release();
	//Z buffer
	D3D11_DEPTH_STENCIL_DESC dsDesc{};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	pDeviceContext->OMSetDepthStencilState(pDSState.Get(), 1);

	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth{};
	descDepth.Width = 700;
	descDepth.Height = 500;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDepthStectilView = {};
	descDepthStectilView.Format = DXGI_FORMAT_D32_FLOAT;
	descDepthStectilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepthStectilView.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDepthStectilView, &pDepthStencilView);

	// bind depth stensil view to OM
	pDeviceContext->OMSetRenderTargets(1u, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());
}

void WindowHandler_D3D11::compileShaders(std::string vertexFile, std::string pixelFile)
{
	std::ifstream inFile(vertexFile, std::ios_base::binary);
	m_VertexBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();
	
	HRESULT result = pDevice->CreateVertexShader(
		m_VertexBytecode.c_str(), m_VertexBytecode.size(),
		nullptr, &pVertexShader);
	assert(SUCCEEDED(result));

	pDeviceContext->VSSetShader(pVertexShader.Get(), 0, 0);



	inFile = std::ifstream{ pixelFile, std::ios_base::binary };
	m_PixelBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();

	result = pDevice->CreatePixelShader(
		m_PixelBytecode.c_str(), m_PixelBytecode.size(),
		nullptr, &pPixelShader);

	pDeviceContext->PSSetShader(pPixelShader.Get(), 0, 0);
}

void WindowHandler_D3D11::SetupShaderBuffers()
{
	D3D11_BUFFER_DESC constantBuffer_DESC{};
	constantBuffer_DESC.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBuffer_DESC.Usage = D3D11_USAGE_DYNAMIC;
	constantBuffer_DESC.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBuffer_DESC.MiscFlags = 0u;
	constantBuffer_DESC.ByteWidth = sizeof(DirectX::XMMATRIX);
	constantBuffer_DESC.StructureByteStride = 0u;
	pDevice->CreateBuffer(&constantBuffer_DESC, NULL, &pConstantBuffer);
}