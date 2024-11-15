#include "Texture.h"
#include "Rev_CoreSystems.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Rev;

void Texture::LoadTexture(const char* path)
{
	TextureData data;

	m_ImageData = stbi_load(path,
		&data.ImageWidth,
		&data.ImageHeight,
		&data.ImageChannels, data.ImageDesiredChannels);
	assert(m_ImageData);
}