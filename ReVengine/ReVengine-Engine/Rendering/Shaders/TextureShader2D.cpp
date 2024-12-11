#include "TextureShader2D.h"
#include <d3dcompiler.h>
#include "Rendering/Texture.h"

using namespace Rev;

TextureShader2D::TextureShader2D(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, Rev::Texture* texture) :
	BaseShader(pDevice, pDeviceContext),
	m_Texture{ texture }
{
	LoadShaders(m_VertexFile, m_PixelFile);
	InitShader();
}

TextureShader2D::~TextureShader2D()
{

}

void TextureShader2D::InitShader()
{
	SetupInputLayer();
	SetupShaderBuffers();
	SetupImageSampler();
	SetupTexture(m_Texture);
	SetupShaderResourceView();
}

void TextureShader2D::SetShader()
{
	m_DeviceContext->PSSetShaderResources(0, 1, m_ImageShaderResourceView.GetAddressOf());
	m_DeviceContext->PSSetSamplers(0, 1, m_ImageSamplerState.GetAddressOf());
}

void TextureShader2D::SetupShaderBuffers()
{
	D3D11_BUFFER_DESC matrixBuffer_DESC{};
	matrixBuffer_DESC.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBuffer_DESC.Usage = D3D11_USAGE_DYNAMIC;
	matrixBuffer_DESC.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBuffer_DESC.MiscFlags = 0;
	matrixBuffer_DESC.ByteWidth = sizeof(MatrixBufferType);
	matrixBuffer_DESC.StructureByteStride = 0;
	m_Device->CreateBuffer(&matrixBuffer_DESC, NULL, &m_MatrixBuffer);
}
void TextureShader2D::SetupImageSampler()
{
	D3D11_SAMPLER_DESC ImageSamplerDesc = {};

	ImageSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	ImageSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	ImageSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	ImageSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	ImageSamplerDesc.MipLODBias = 0.0f;
	ImageSamplerDesc.MaxAnisotropy = 1;
	ImageSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	ImageSamplerDesc.BorderColor[0] = 1.0f;
	ImageSamplerDesc.BorderColor[1] = 1.0f;
	ImageSamplerDesc.BorderColor[2] = 1.0f;
	ImageSamplerDesc.BorderColor[3] = 1.0f;
	ImageSamplerDesc.MinLOD = -FLT_MAX;
	ImageSamplerDesc.MaxLOD = FLT_MAX;

	HRESULT result = m_Device->CreateSamplerState(&ImageSamplerDesc,
		&m_ImageSamplerState);

	assert(SUCCEEDED(result));
}
void TextureShader2D::SetupTexture(Rev::Texture* texture)
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

	HRESULT result = m_Device->CreateTexture2D(&ImageTextureDesc,
		&ImageSubresourceData,
		&m_ImageTexture
	);

	assert(SUCCEEDED(result));
}
void TextureShader2D::SetupShaderResourceView()
{
	HRESULT result = m_Device->CreateShaderResourceView(m_ImageTexture.Get(),
		nullptr,
		&m_ImageShaderResourceView
	);
	assert(SUCCEEDED(result));
}