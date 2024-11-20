#pragma once

#include "d3d11.h"
#include <string>
#include <DirectXMath.h>
#include "wrl.h"
	namespace wrl = Microsoft::WRL;

namespace Rev {
	class Texture;
}

namespace RevDev
{
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX transform;
	};

	class TextureShader
	{
	public:
		TextureShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, Rev::Texture* texture);
		~TextureShader();

		void InitShader();
		void SetShader(); //Every frame

		std::string GetVertexByteCode() { return m_VertexBytecode; }
		wrl::ComPtr<ID3D11Buffer> GetMatrixBuffer() { return m_MatrixBuffer; }

	private:
		void SetupInputLayer();
		void SetupTexture(Rev::Texture* texture);
		void SetupShaderResourceView();
		void SetupShaderBuffers();
		void SetupImageSampler();

		void LoadShaders(std::string vertexFile, std::string pixelFile);
		HRESULT CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob);

	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;

		Rev::Texture* m_Texture;

		std::string m_VertexFile = "../engine_resources/shaders/VertexShader.hlsl";
		std::string m_PixelFile = "../engine_resources/shaders/PixelShader.hlsl";

		wrl::ComPtr<ID3D11VertexShader> m_VertexShader = NULL;
		wrl::ComPtr<ID3D11PixelShader> m_PixelShader = NULL;

		std::string m_VertexBytecode;

		wrl::ComPtr<ID3D11Buffer> m_MatrixBuffer;

		wrl::ComPtr<ID3D11SamplerState> m_ImageSamplerState;
		wrl::ComPtr<ID3D11Texture2D> m_ImageTexture;
		wrl::ComPtr<ID3D11ShaderResourceView> m_ImageShaderResourceView;
	};
}