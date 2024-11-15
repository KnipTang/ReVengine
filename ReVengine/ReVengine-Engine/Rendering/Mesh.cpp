#include "Mesh.h"
#include "d3d11.h"
#include "Rendering/Direct3D11/WindowHandler.h"
#include "Utils/Vertex.h"
#include "Texture.h"

using namespace RevDev;

uint32_t Mesh::meshIDCounter = 0;

Mesh::Mesh(ID3D11Device* pDevice) :
	m_Device{pDevice},
	m_IndiceCount{},
	meshID{meshIDCounter++}
{
}

Mesh::~Mesh()
{

}

void Mesh::setupVertexBuffer(const std::vector<Vertex> vertices)
{
	D3D11_BUFFER_DESC vertexBuffer_DESC{ 0 };
	vertexBuffer_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER; //Type of vertex buffer
	vertexBuffer_DESC.Usage = D3D11_USAGE_DEFAULT; //How buffer communicates with gpu (if the gpu can also write back to the cpu or not)
	vertexBuffer_DESC.CPUAccessFlags = 0;
	vertexBuffer_DESC.MiscFlags = 0;
	vertexBuffer_DESC.ByteWidth = UINT(vertices.size() * sizeof(Vertex));
	vertexBuffer_DESC.StructureByteStride = sizeof(Vertex);

	//The data of the vertex
	D3D11_SUBRESOURCE_DATA subResc_DATA{ 0 };
	subResc_DATA.pSysMem = vertices.data();

	HRESULT result = m_Device->CreateBuffer(&vertexBuffer_DESC, &subResc_DATA, &m_VertexBuffer);
	assert(SUCCEEDED(result));
}

void Mesh::setupIndexBuffer(const std::vector<unsigned short> indices) 
{
	D3D11_BUFFER_DESC indexBuffer_DESC{};
	indexBuffer_DESC.BindFlags = D3D11_BIND_INDEX_BUFFER; //Type of vertex buffer
	indexBuffer_DESC.Usage = D3D11_USAGE_DEFAULT; //How buffer communicates with gpu (if the gpu can also write back to the cpu or not)
	indexBuffer_DESC.CPUAccessFlags = 0;
	indexBuffer_DESC.MiscFlags = 0;
	indexBuffer_DESC.ByteWidth = UINT(indices.size() * sizeof(unsigned short));
	indexBuffer_DESC.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA subRescIndex_DATA{ 0 };
	subRescIndex_DATA.pSysMem = indices.data();

	HRESULT result = m_Device->CreateBuffer(&indexBuffer_DESC, &subRescIndex_DATA, &m_IndexBuffer);
	assert(SUCCEEDED(result));

	m_IndiceCount = UINT(indices.size());
}

wrl::ComPtr<ID3D11ShaderResourceView> Mesh::SetupTexture(Rev::Texture* texture)
{
	wrl::ComPtr<ID3D11Texture2D> imageTexture = CreateTexture(texture);
	return ShaderResourceView(imageTexture);
}

wrl::ComPtr<ID3D11Texture2D> Mesh::CreateTexture(Rev::Texture* texture)
{
	auto&& data = texture->GetTextureDate();
	auto&& imageData = texture->GetImageData();

	int ImagePitch = data->ImageWidth * 4;

	D3D11_TEXTURE2D_DESC ImageTextureDesc = {};

	ImageTextureDesc.Width = (UINT)data->ImageWidth;
	ImageTextureDesc.Height = (UINT)data->ImageHeight;
	ImageTextureDesc.MipLevels = 1;
	ImageTextureDesc.ArraySize = 1;
	ImageTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	ImageTextureDesc.SampleDesc.Count = 1;
	ImageTextureDesc.SampleDesc.Quality = 0;
	ImageTextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	ImageTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA ImageSubresourceData = {};

	ImageSubresourceData.pSysMem = imageData;
	ImageSubresourceData.SysMemPitch = ImagePitch;

	wrl::ComPtr<ID3D11Texture2D> ImageTexture;

	HRESULT result = m_Device->CreateTexture2D(&ImageTextureDesc,
		&ImageSubresourceData,
		&ImageTexture
	);

	assert(SUCCEEDED(result));

	return ImageTexture;
}

wrl::ComPtr<ID3D11ShaderResourceView> Mesh::ShaderResourceView(wrl::ComPtr<ID3D11Texture2D> imageTexture)
{
	ID3D11ShaderResourceView* ImageShaderResourceView;

	HRESULT result = m_Device->CreateShaderResourceView(imageTexture.Get(),
		nullptr,
		&ImageShaderResourceView
	);
	assert(SUCCEEDED(result));

	return ImageShaderResourceView;
}