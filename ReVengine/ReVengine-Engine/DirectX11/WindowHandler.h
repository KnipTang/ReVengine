#include "d3d11.h"
#include "SDL.h"
#include <SDL_syswm.h>
#include <string>
#include "wrl.h"

//Using comPtr's to manage windows objects in a smart way
namespace wrl = Microsoft::WRL;

class D3D11Creator
{
public:
	D3D11Creator(SDL_Window* window);
	~D3D11Creator();

	void setupDeviceAndSwap();
	void endFrame(); //Set backbuffer to pass to and create rendertargetview
	void clearBuffer(float background_colour[4]); //Set background color and clear back buffer
	void compileShaders();

	void cleanup();
	void updateWindow();
	void renderWindow();


private:
	//The head of directX From device all the other achitecture gets created and linked to.
	wrl::ComPtr<ID3D11Device> pDevice = NULL; //A device is used to create resources and to enumerate the capabilities of a display adapter

	//Used to execute commands to the gpu, draw calls,..
	wrl::ComPtr<ID3D11DeviceContext> pDeviceContext = NULL; //A device context contains the circumstance or setting in which a device is used. More specifically, a device context is used to set pipeline state and generate rendering commands using the resources owned by a device.
	
	//Swaps between textures, once the back is done calculating, the back becomes the front and the process starts again.
	wrl::ComPtr<IDXGISwapChain> pSwapChain = NULL;

	
	wrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView = NULL;

	//Holds both back and front chain. (front is what the user sees, back is what is being calculated before the user sees it)
	wrl::ComPtr<ID3D11Texture2D> pFramebuffer;

	wrl::ComPtr<ID3D11VertexShader> _vertexShader = NULL;
	wrl::ComPtr<ID3D11PixelShader> _pixelShader = NULL;
	wrl::ComPtr<ID3D11InputLayout> input_layout_ptr = NULL;

	wrl::ComPtr<ID3D11Buffer> vertex_buffer_ptr = NULL;
	UINT vertex_stride = 3 * sizeof(float);
	UINT vertex_offset = 0;
	UINT vertex_count = 3;

	//Windows window handle.
	HWND hwnd;

	std::string vertexFile = "../DirectX11/shaders/shader.cso";
	std::string pixelFile = "../DirectX11/shaders/shader_p.cso";
};

