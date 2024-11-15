#include "Texture.h"
#include "Rev_CoreSystems.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Rev;

Texture::Texture(std::string path)
{
	LoadTexture(path.c_str());
}

Texture::~Texture()
{

}

void Texture::LoadTexture(const char* path)
{
	m_TextureDate = std::make_unique<TextureData>();

	m_ImageData = stbi_load(
		path,
		&m_TextureDate->ImageWidth,
		&m_TextureDate->ImageHeight,
		&m_TextureDate->ImageChannels, 
		m_TextureDate->ImageDesiredChannels
	);
	assert(m_ImageData);
}