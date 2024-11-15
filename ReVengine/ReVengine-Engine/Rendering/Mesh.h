#pragma once

#include <vector>
#include "wrl.h"
#include "d3d11.h"
#undef PlaySound

namespace wrl = Microsoft::WRL;

//class ID3D11Device;
//class ID3D11Buffer;
class Texture;
struct Vertex;

namespace RevDev
{
	class Mesh
	{
	public:
		Mesh(ID3D11Device* pDevice);
		~Mesh();

		void CreateTexture();
		void setupVertexBuffer(const std::vector<Vertex> vertices);
		void setupIndexBuffer(const std::vector<unsigned short> indices);

		const int GetID() { return meshID; }
		wrl::ComPtr<ID3D11Buffer> GetVertexBuffer() { return m_VertexBuffer; }
		wrl::ComPtr<ID3D11Buffer> GetIndexBuffer() { return m_IndexBuffer; }
		const UINT GetIndiceCount() { return m_IndiceCount; }

	private:
		unsigned char* m_ImageData;

		wrl::ComPtr<ID3D11Buffer> m_VertexBuffer;
		wrl::ComPtr<ID3D11Buffer> m_IndexBuffer;
		UINT m_IndiceCount;

		ID3D11Device* m_Device;

		Texture* m_Texture;

		static int meshIDCounter;
		int meshID;
	};
}