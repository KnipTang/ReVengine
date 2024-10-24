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

namespace RevDev
{
	class D3D11Creator
	{
	public:
		D3D11Creator(SDL_Window* window, int windowWidth, int windowHeight);
		~D3D11Creator();

		void setupDeviceAndSwap();
		void endFrame(); //Set backbuffer to pass to and create rendertargetview
		void clearBuffer(float background_colour[4]); //Set background color and clear back buffer
		void compileShaders();

		void drawTriangle(float angle, float x, float z);

		void updateWindow();

		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			} pos;
			struct
			{
				float r;
				float g;
				float b;
			} color;
		};

		struct ConstantBuffer
		{
			DirectX::XMMATRIX transform;
		};

	private:
		//The head of directX From device all the other achitecture gets created and linked to.
		wrl::ComPtr<ID3D11Device> pDevice = NULL; //A device is used to create resources and to enumerate the capabilities of a display adapter

		//Used to execute commands to the gpu, draw calls,.. // Sets the settings of the pipeline(What shaders to use, what options (on those shaders))
		wrl::ComPtr<ID3D11DeviceContext> pDeviceContext = NULL; //A device context contains the circumstance or setting in which a device is used. More specifically, a device context is used to set pipeline state and generate rendering commands using the resources owned by a device.
	
		//Swaps between textures, once the back is done calculating, the back becomes the front and the process starts again.
		wrl::ComPtr<IDXGISwapChain> pSwapChain = NULL;

		//Used to specifiy which pixel is being targeted atm
		wrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView = NULL;

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
		float width;
		float height;

		std::string vertexFile = "../DirectX11/shaders/VertexShader.cso";
		std::string pixelFile = "../DirectX11/shaders/PixelShader.cso";

		float background_colour[4] = { 0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f };

		std::chrono::steady_clock::time_point last;

	};
}
