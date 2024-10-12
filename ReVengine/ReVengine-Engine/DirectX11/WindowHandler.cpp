#include "DirectX11/WindowHandler.h"
#include <cassert>
#include "SDL.h"
#include <SDL_syswm.h>
#include "d3dcompiler.h"
#include <string>
#include <iostream>
#include "filesystem"
#include "fstream"

void displayCurrentFiles(std::string path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path() << std::endl;
}

D3D11Creator::D3D11Creator()
{
}

D3D11Creator::~D3D11Creator()
{
}

void D3D11Creator::createDevice()
{
	//HRESULT hr = D3D11CreateDevice();
	//assert(SUCCEEDED(hr)); //Succeeded checks if the function worked and assert crashes the program if it didnt succeed
	//_device.cre
}

void D3D11Creator::setupSwapChain(SDL_Window* window)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	hwnd = wmInfo.info.win.window;



	DXGI_SWAP_CHAIN_DESC swapChainDESC = { 0 };
	ZeroMemory(&swapChainDESC, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDESC.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDESC.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDESC.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDESC.SampleDesc.Count = 1;
	swapChainDESC.SampleDesc.Quality = 0;
	swapChainDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDESC.BufferCount = 1;
	swapChainDESC.OutputWindow = hwnd;
	swapChainDESC.Windowed = true;



	D3D_FEATURE_LEVEL feature_level;
	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDESC,
		&_swapChain,
		&_device,
		&feature_level,
		&_deviceContext);
	assert(S_OK == hr && _swapChain && _device && _deviceContext);



	hr = _swapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&framebuffer);
	assert(SUCCEEDED(hr));
	hr = _device->CreateRenderTargetView(
		framebuffer, 0, &_renderTargetView);
	assert(SUCCEEDED(hr));
	framebuffer->Release();

	displayCurrentFiles("../DirectX11/shaders");

	compileShaders();
}

void D3D11Creator::compileShaders()
{
	std::ifstream inFile(vertexFile, std::ios_base::binary);
	std::string vertexBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();

	HRESULT result = _device->CreateVertexShader(
		vertexBytecode.c_str(), vertexBytecode.size(),
		nullptr, &_vertexShader);
	assert(SUCCEEDED(result));

	inFile = std::ifstream{ pixelFile, std::ios_base::binary };
	std::string pixelBytecode = std::string(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>());
	inFile.close();

	result = _device->CreatePixelShader(
		pixelBytecode.c_str(), pixelBytecode.size(),
		nullptr, &_pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
	  { 
			"POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  /*
	  { "COL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  { "NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  { "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  */
	};
	result = _device->CreateInputLayout(
		inputElementDesc,
		ARRAYSIZE(inputElementDesc),
		vertexBytecode.c_str(),
		vertexBytecode.size(),
		&input_layout_ptr);
	assert(SUCCEEDED(result));

	float vertex_data_array[] = {
   0.0f,  0.5f,  0.0f, // point at top
   0.5f, -0.5f,  0.0f, // point at bottom-right
  -0.5f, -0.5f,  0.0f, // point at bottom-left
	};


	{ /*** load mesh data into vertex buffer **/
		D3D11_BUFFER_DESC vertex_buff_descr = {};
		vertex_buff_descr.ByteWidth = sizeof(vertex_data_array);
		vertex_buff_descr.Usage = D3D11_USAGE_DEFAULT;
		vertex_buff_descr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA sr_data = { 0 };
		sr_data.pSysMem = vertex_data_array;
		HRESULT hr = _device->CreateBuffer(
			&vertex_buff_descr,
			&sr_data,
			&vertex_buffer_ptr);
		assert(SUCCEEDED(hr));
	}
}

void D3D11Creator::updateWindow()
{
	/* clear the back buffer to cornflower blue for the new frame */
	float background_colour[4] = {
	  0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f };
	_deviceContext->ClearRenderTargetView(
		_renderTargetView, background_colour);

	RECT winRect;
	GetClientRect(hwnd, &winRect);
	D3D11_VIEWPORT viewport = {
	  0.0f,
	  0.0f,
	  (FLOAT)(winRect.right - winRect.left),
	  (FLOAT)(winRect.bottom - winRect.top),
	  0.0f,
	  1.0f };
	_deviceContext->RSSetViewports(1, &viewport);

	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);

	_deviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_deviceContext->IASetInputLayout(input_layout_ptr);
	_deviceContext->IASetVertexBuffers(
		0,
		1,
		&vertex_buffer_ptr,
		&vertex_stride,
		&vertex_offset);

	_deviceContext->VSSetShader(_vertexShader, NULL, 0);
	_deviceContext->PSSetShader(_pixelShader, NULL, 0);

	_deviceContext->Draw(vertex_count, 0);

	_swapChain->Present(1, 0);
}

void D3D11Creator::renderWindow()
{

}

void D3D11Creator::cleanup()
{

}