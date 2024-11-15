#pragma once

#include <memory>
#include <functional>

namespace Rev
{
	struct TextureData
	{
		int ImageWidth;
		int ImageHeight;
		int ImageChannels;
		int ImageDesiredChannels = 4;
	};

	class Texture
	{
	public:
		Texture();
		~Texture();

		void LoadTexture(const char* path);

	private:
		unsigned char* m_ImageData;
	};
}