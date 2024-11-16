#pragma once

#include <vector>
#include "wrl.h"
#include "d3d11.h"
#include <memory>
#undef PlaySound

namespace wrl = Microsoft::WRL;

struct Vertex;

namespace Rev
{
	class Texture;
}

namespace RevDev
{
	class TextureShader;
}

namespace RevDev
{
	class Mesh
	{
	public:
		Mesh(ID3D11Device* pDevice, TextureShader* textureShader);
		~Mesh();

		void setupVertexBuffer(const std::vector<Vertex> vertices);
		void setupIndexBuffer(const std::vector<unsigned short> indices);

		const uint32_t GetID() { return meshID; }
		wrl::ComPtr<ID3D11Buffer> GetVertexBuffer() { return m_VertexBuffer; }
		wrl::ComPtr<ID3D11Buffer> GetIndexBuffer() { return m_IndexBuffer; }
		const UINT GetIndiceCount() { return m_IndiceCount; }

		TextureShader* GetTextureShader() { return m_TextureShader; }
	private:

	private:
		ID3D11Device* m_Device;

		wrl::ComPtr<ID3D11Buffer> m_VertexBuffer;
		wrl::ComPtr<ID3D11Buffer> m_IndexBuffer;
		UINT m_IndiceCount;

		TextureShader* m_TextureShader;

		static uint32_t meshIDCounter;
		uint32_t meshID;
	};
}