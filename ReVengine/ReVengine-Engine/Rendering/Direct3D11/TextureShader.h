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
	class TextureShader
	{
	public:
		TextureShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, Rev::Texture* texture);
		~TextureShader();

		void compileShaders(std::string vertexFile, std::string pixelFile);
		void SetupShaderBuffers();
		void SetupImageSampler();

		wrl::ComPtr<ID3D11ShaderResourceView> SetupTexture();

		std::string GetVertexByteCode() { return m_VertexBytecode; }
		wrl::ComPtr<ID3D11Buffer> GetConstantBuffer() { return pConstantBuffer; }

	private:
		[[nodiscard]]
		wrl::ComPtr<ID3D11Texture2D> CreateTexture(Rev::Texture* texture);
		wrl::ComPtr<ID3D11ShaderResourceView> ShaderResourceView(wrl::ComPtr<ID3D11Texture2D> imageTexture);
		HRESULT CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob);

		void SetupInputLayer();

	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;

		Rev::Texture* m_Texture;

		std::string m_VertexFile = "../engine_resources/shaders/VertexShader.hlsl";
		std::string m_PixelFile = "../engine_resources/shaders/PixelShader.hlsl";

		wrl::ComPtr<ID3D11VertexShader> m_VertexShader = NULL;
		wrl::ComPtr<ID3D11PixelShader> m_PixelShader = NULL;

		std::string m_VertexBytecode;

		wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	};
}