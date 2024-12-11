#pragma once

#include "d3d11.h"
#include <string>
#include <DirectXMath.h>
#include "wrl.h"
namespace wrl = Microsoft::WRL;

namespace Rev {
	class Texture;
}

namespace Rev
{
	class BaseShader
	{
	public:
		BaseShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
		~BaseShader() = default;

		std::string GetVertexByteCode() { return m_VertexBytecode; }

	protected:
		virtual void SetupInputLayer(); //Optionally overwritten

		void LoadShaders(std::string vertexFile, std::string pixelFile);
		HRESULT CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob);

	protected:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;

		wrl::ComPtr<ID3D11VertexShader> m_VertexShader = NULL;
		wrl::ComPtr<ID3D11PixelShader> m_PixelShader = NULL;

		std::string m_VertexBytecode;
	private:

	};
}