#pragma once

#include <vector>
#include "wrl.h"
#include "d3d11.h"
#undef PlaySound

namespace wrl = Microsoft::WRL;

struct Vertex;

namespace Rev
{
	class Texture;
}

namespace RevDev
{
	class Mesh
	{
	public:
		Mesh(ID3D11Device* pDevice);
		~Mesh();

		void setupVertexBuffer(const std::vector<Vertex> vertices);
		void setupIndexBuffer(const std::vector<unsigned short> indices);

		void SetupTexture(Rev::Texture* texture);
		//wrl::ComPtr<ID3D11Texture2D> GetImageTexture() { return m_ImageTexture; }

		const uint32_t GetID() { return meshID; }
		wrl::ComPtr<ID3D11Buffer> GetVertexBuffer() { return m_VertexBuffer; }
		wrl::ComPtr<ID3D11Buffer> GetIndexBuffer() { return m_IndexBuffer; }
		const UINT GetIndiceCount() { return m_IndiceCount; }

	private:
		[[nodiscard]]
		wrl::ComPtr<ID3D11Texture2D> CreateTexture(Rev::Texture* texture);
		void ShaderResourceView(wrl::ComPtr<ID3D11Texture2D> imageTexture);

	private:
		ID3D11Device* m_Device;

		wrl::ComPtr<ID3D11Buffer> m_VertexBuffer;
		wrl::ComPtr<ID3D11Buffer> m_IndexBuffer;
		UINT m_IndiceCount;

		//wrl::ComPtr<ID3D11Texture2D> m_ImageTexture;

		static uint32_t meshIDCounter;
		uint32_t meshID;
	};
}