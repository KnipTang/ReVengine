#include "d3d11.h"
#include "SDL.h"
#include <SDL_syswm.h>
class D3D11Creator
{
public:
	D3D11Creator();
	~D3D11Creator();

	void createDevice();
	void setupSwapChain(SDL_Window* window);
	void compileShaders();

	void cleanup();
	void updateWindow();
	void renderWindow();
private:
	ID3D11Device* _device = NULL; //A device is used to create resources and to enumerate the capabilities of a display adapter
	ID3D11DeviceContext* _deviceContext = NULL; //A device context contains the circumstance or setting in which a device is used. More specifically, a device context is used to set pipeline state and generate rendering commands using the resources owned by a device.
	IDXGISwapChain* _swapChain = NULL;
	ID3D11RenderTargetView* _renderTargetView = NULL;
};

