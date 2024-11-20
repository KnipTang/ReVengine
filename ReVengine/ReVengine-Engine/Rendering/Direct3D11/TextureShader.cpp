#include "TextureShader.h"
#include <d3dcompiler.h>
#include "Rendering/Texture.h"

using namespace RevDev;

TextureShader::TextureShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, Rev::Texture* texture) :
	m_Device{ pDevice },
	m_DeviceContext { pDeviceContext },
	m_Texture{ texture }
{
	LoadShaders(m_VertexFile, m_PixelFile);
	InitShader();
}

TextureShader::~TextureShader()
{

}

void TextureShader::InitShader()
{
	SetupInputLayer();
	SetupShaderBuffers();
	SetupImageSampler();
	SetupTexture(m_Texture);
	SetupShaderResourceView();
}

void TextureShader::SetShader()
{
	m_DeviceContext->PSSetShaderResources(0, 1, m_ImageShaderResourceView.GetAddressOf());
	m_DeviceContext->PSSetSamplers(0, 1, m_ImageSamplerState.GetAddressOf());
}


void TextureShader::SetupInputLayer()
{
	//Explain layout of vertices
	wrl::ComPtr<ID3D11InputLayout> inputLayer;
	const D3D11_INPUT_ELEMENT_DESC inputElement_DESC[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	m_Device->CreateInputLayout(inputElement_DESC, std::size(inputElement_DESC), m_VertexBytecode.c_str(), m_VertexBytecode.size(), &inputLayer);

	m_DeviceContext->IASetInputLayout(inputLayer.Get());
}
void TextureShader::SetupShaderBuffers()
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
void TextureShader::SetupImageSampler()
{
	D3D11_SAMPLER_DESC ImageSamplerDesc = {};

	ImageSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	ImageSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	ImageSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	ImageSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
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
void TextureShader::SetupTexture(Rev::Texture* texture)
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
void TextureShader::SetupShaderResourceView()
{
	HRESULT result = m_Device->CreateShaderResourceView(m_ImageTexture.Get(),
		nullptr,
		&m_ImageShaderResourceView
	);
	assert(SUCCEEDED(result));
}

void TextureShader::LoadShaders(std::string vertexFile, std::string pixelFile)
{
	std::wstring wideVertexFile = std::wstring(vertexFile.begin(), vertexFile.end());
	ID3DBlob* vsBlob = nullptr;
	HRESULT hr = CompileShader(wideVertexFile.c_str(), "vs_main", "vs_5_0", &vsBlob);
	if (FAILED(hr))
	{
		printf("Failed compiling vertex shader %08X\n", hr);
	}

	std::wstring widePixelFile = std::wstring(pixelFile.begin(), pixelFile.end());
	ID3DBlob* psBlob = nullptr;
	hr = CompileShader(widePixelFile.c_str(), "ps_main", "ps_5_0", &psBlob);
	if (FAILED(hr))
	{
		printf("Failed compiling pixel shader %08X\n", hr);
	}

	//std::ifstream inFile(vertexFile, std::ios_base::binary);
	//m_VertexBytecode = std::string(std::istreambuf_iterator<char>(inFile),
	//	std::istreambuf_iterator<char>());
	//inFile.close();
	m_VertexBytecode.assign((char*)vsBlob->GetBufferPointer(), (char*)vsBlob->GetBufferPointer() + vsBlob->GetBufferSize());

	hr = m_Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_VertexShader);
	if (FAILED(hr))
	{
		printf("Failed creating vertex shader %08X\n", hr);
	}
	m_DeviceContext->VSSetShader(m_VertexShader.Get(), 0, 0);

	hr = m_Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_PixelShader);
	if (FAILED(hr))
	{
		printf("Failed creating pixel shader %08X\n", hr);
	}

	m_DeviceContext->PSSetShader(m_PixelShader.Get(), 0, 0);
}
HRESULT TextureShader::CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob)
{
	if (!srcFile || !entryPoint || !profile || !blob)
		return E_INVALIDARG;

	*blob = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(srcFile, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint, profile,
		flags, 0, &shaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}

		if (shaderBlob)
			shaderBlob->Release();

		return hr;
	}

	*blob = shaderBlob;

	return hr;
}