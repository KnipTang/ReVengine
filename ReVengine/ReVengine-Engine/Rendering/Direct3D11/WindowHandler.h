#pragma once

#include "d3d11.h"
#include "SDL.h"
#include <SDL_syswm.h>
#include <string>
#include "wrl.h"
#include "chrono"
#include <DirectXMath.h>

//Using comPtr's to manage windows objects in a smart way
namespace wrl = Microsoft::WRL;

struct Vertex;

namespace RevDev
{
	class WindowHandler_D3D11
	{
	public:


		WindowHandler_D3D11(SDL_Window* window, int windowWidth, int windowHeight);
		~WindowHandler_D3D11();

		void setupPipeline();

		void setupDeviceAndSwap();
		void SetupRenderTargetAndStencelBuffer(); //Set backbuffer to pass to and create rendertargetview

		void compileShaders(std::string vertexFile, std::string pixelFile);
		void setupShader(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices);

		void clearBuffer(float backgroundColour[4]); //Set background color and clear back buffer

		void drawIt(DirectX::XMMATRIX &transform, UINT count);

		void updateWindow();

	private:
		//The head of directX From device all the other achitecture gets created and linked to.
		wrl::ComPtr<ID3D11Device> pDevice = NULL; //A device is used to create resources and to enumerate the capabilities of a display adapter

		//Used to execute commands to the gpu, draw calls,.. // Sets the settings of the pipeline(What shaders to use, what options (on those shaders))
		wrl::ComPtr<ID3D11DeviceContext> pDeviceContext = NULL; //A device context contains the circumstance or setting in which a device is used. More specifically, a device context is used to set pipeline state and generate rendering commands using the resources owned by a device.
	
		//Swaps between textures, once the back is done calculating, the back becomes the front and the process starts again.
		wrl::ComPtr<IDXGISwapChain> pSwapChain = NULL;

		//Used to specifiy which pixel is being targeted atm
		wrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView = NULL;

		wrl::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

		//Holds both back and front chain. (front is what the user sees, back is what is being calculated before the user sees it)
		wrl::ComPtr<ID3D11Texture2D> pFramebuffer;

		//Buffer that holds the vertex information
		wrl::ComPtr<ID3D11Buffer> pVertexBuffer = NULL;

		wrl::ComPtr<ID3D11VertexShader> pVertexShader = NULL;
		wrl::ComPtr<ID3D11PixelShader> pPixelShader = NULL;
		wrl::ComPtr<ID3D11InputLayout> input_layout_ptr = NULL;

		std::string vertexBytecode;
		std::string pixelBytecode;


		//OffSet between vertecies
		UINT vertexOffset = 0;

		//Windows window handle.
		HWND hwnd;
		int width;
		int height;

		float background_colour[4] = { 0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f };

		std::chrono::steady_clock::time_point last;

		std::vector<unsigned short> vIndices;

		wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	};
}
