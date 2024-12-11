#pragma once

#include "d3d11.h"
#include <string>
#include "wrl.h"
#include "BaseShader.h"
	namespace wrl = Microsoft::WRL;

namespace Rev {
	class Texture;
}

namespace Rev
{
	struct MatrixBufferType
	{
		DirectX::XMMATRIX ortho;
	};

	class TextureShader2D : public Rev::BaseShader
	{
	public:

		TextureShader2D(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, Rev::Texture* texture);
		~TextureShader2D();

		void InitShader();
		void SetShader(); //Every frame

		std::string GetVertexByteCode() { return m_VertexBytecode; }
		wrl::ComPtr<ID3D11Buffer> GetMatrixBuffer() { return m_MatrixBuffer; }

	private:
		void SetupTexture(Rev::Texture* texture);
		void SetupShaderResourceView();
		void SetupShaderBuffers();
		void SetupImageSampler();

	private:
		Rev::Texture* m_Texture;

		wrl::ComPtr<ID3D11Buffer> m_MatrixBuffer;

		wrl::ComPtr<ID3D11SamplerState> m_ImageSamplerState;
		wrl::ComPtr<ID3D11Texture2D> m_ImageTexture;
		wrl::ComPtr<ID3D11ShaderResourceView> m_ImageShaderResourceView;

		std::string m_VertexFile = "../engine_resources/shaders/UI_vs.hlsl";
		std::string m_PixelFile = "../engine_resources/shaders/PixelShader.hlsl";
	};
}