#include "DirectX11/WindowHandler.h"
#include <cassert>
#include "SDL.h"
#include <SDL_syswm.h>
#include "d3dcompiler.h"
#include <string>
#include <iostream>
#include "filesystem"
#include "fstream"

#pragma comment(lib, "d3d11.lib")

D3D11Creator::D3D11Creator(SDL_Window* window, int windowWidth, int windowHeight)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	hwnd = wmInfo.info.win.window;

	width = windowWidth;
	height = windowHeight;
}

D3D11Creator::~D3D11Creator()
{
	
	if (pDeviceContext != nullptr)
		pDeviceContext->Release();

	if (pSwapChain != nullptr)
		pSwapChain->Release();
}

void D3D11Creator::setupDeviceAndSwap()
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


	endFrame();

	compileShaders();
}

void D3D11Creator::endFrame()
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

	pFramebuffer->Release();

}

void D3D11Creator::clearBuffer(float background_colour[4])
{
	pDeviceContext->ClearRenderTargetView(
		pRenderTargetView.Get(), background_colour);
}

void D3D11Creator::compileShaders()
{
	std::ifstream inFile(vertexFile, std::ios_base::binary);
	vertexBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();
	
	HRESULT result = pDevice->CreateVertexShader(
		vertexBytecode.c_str(), vertexBytecode.size(),
		nullptr, &pVertexShader);
	assert(SUCCEEDED(result));

	inFile = std::ifstream{ pixelFile, std::ios_base::binary };
	pixelBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();

	result = pDevice->CreatePixelShader(
		pixelBytecode.c_str(), pixelBytecode.size(),
		nullptr, &pPixelShader);
}

void D3D11Creator::drawTriangle()
{
	const Vertex vertices[]
	{
		{ 0.0f, 0.5f },		
		{ 0.5f, -0.5f },
		{ -0.5f, -0.5f },
	};

	D3D11_BUFFER_DESC vertexBuffer_DESC{ 0 };
	vertexBuffer_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER; //Type of vertex buffer
	vertexBuffer_DESC.Usage = D3D11_USAGE_DEFAULT; //How buffer communicates with gpu (if the gpu can also write back to the cpu or not)
	vertexBuffer_DESC.CPUAccessFlags = 0;
	vertexBuffer_DESC.MiscFlags = 0;
	vertexBuffer_DESC.ByteWidth = sizeof(vertices);
	vertexBuffer_DESC.StructureByteStride = sizeof(Vertex);

	//The data of the vertex
	D3D11_SUBRESOURCE_DATA subResc_DATA{ 0 };
	subResc_DATA.pSysMem = vertices;

	HRESULT result = pDevice->CreateBuffer(&vertexBuffer_DESC, &subResc_DATA, &pVertexBuffer);
	assert(SUCCEEDED(result));

	//Vertex buffer is a buffer that holds the vertex data
	pDeviceContext->IASetVertexBuffers(0,1, pVertexBuffer.GetAddressOf(), &vertexStride, &vertexOffset);

	pDeviceContext->VSSetShader(pVertexShader.Get(), 0, 0);

	pDeviceContext->PSSetShader(pPixelShader.Get(), 0, 0);

	//specifies where the pixel shader has to the pixel target to
	pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);

	//Config viewport -> pixelshader target (renderTarget) From ndc to render view
	D3D11_VIEWPORT viewPort;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pDeviceContext->RSSetViewports(1, &viewPort);

	//Set type of rendering (point, line (strip), triangle (strip),.... Strip -> 0,1,2,3,4... Non-Strip = (0 - 1), (1 - 2), (5 - 0),...
	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Explain layout of vertices
	wrl::ComPtr<ID3D11InputLayout> inputLayer;
	const D3D11_INPUT_ELEMENT_DESC inputElement_DESC[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	pDevice->CreateInputLayout(inputElement_DESC, std::size(inputElement_DESC), vertexBytecode.c_str(), vertexBytecode.size(), &inputLayer);

	pDeviceContext->IASetInputLayout(inputLayer.Get());

	UINT vertexCount = std::size(vertices);
	pDeviceContext->Draw(vertexCount, 0);
}

void D3D11Creator::updateWindow()
{
	clearBuffer(background_colour);
	drawTriangle();

	pSwapChain->Present(1, 0);

}