#include "Texture.h"
#include "Rev_CoreSystems.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Rev;

void Texture::LoadTexture(const char* path)
{
	int ImageWidth;
	int ImageHeight;
	int ImageChannels;
	int ImageDesiredChannels = 4;

	m_ImageData = stbi_load(path,
		&ImageWidth,
		&ImageHeight,
		&ImageChannels, ImageDesiredChannels);
	assert(m_ImageData);
}