#include "DirectX11/WindowHandler.h"
#include <cassert>
#include "SDL.h"
#include <SDL_syswm.h>
#include "d3dcompiler.h"
#include <string>
#include <iostream>
#include "filesystem"

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
	HWND hwnd = wmInfo.info.win.window;



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



	ID3D11Texture2D* framebuffer;
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
}

void D3D11Creator::compileShaders()
{
//	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//	flags |= D3DCOMPILE_DEBUG; // add more debug output
//#endif
//	ID3DBlob* vs_blob_ptr = NULL, * ps_blob_ptr = NULL, * error_blob = NULL;
//
//	// COMPILE VERTEX SHADER
//	HRESULT hr = D3DCompileFromFile(
//		L"shader.hlsl",
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,
//		"vs_main",
//		"vs_5_0",
//		flags,
//		0,
//		&vs_blob_ptr,
//		&error_blob);
//	if (FAILED(hr)) {
//		if (error_blob) {
//			OutputDebugStringA((char*)error_blob->GetBufferPointer());
//			error_blob->Release();
//		}
//		if (vs_blob_ptr) { vs_blob_ptr->Release(); }
//		assert(false);
//	}
//
//	// COMPILE PIXEL SHADER
//	hr = D3DCompileFromFile(
//		L"shader.hlsl",
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,
//		"ps_main",
//		"ps_5_0",
//		flags,
//		0,
//		&ps_blob_ptr,
//		&error_blob);
//	if (FAILED(hr)) {
//		if (error_blob) {
//			OutputDebugStringA((char*)error_blob->GetBufferPointer());
//			error_blob->Release();
//		}
//		if (ps_blob_ptr) { ps_blob_ptr->Release(); }
//		assert(false);
//	}
}

void D3D11Creator::updateWindow()
{

}

void D3D11Creator::renderWindow()
{

}

void D3D11Creator::cleanup()
{

}