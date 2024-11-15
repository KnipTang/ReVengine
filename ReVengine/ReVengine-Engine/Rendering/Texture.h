#pragma once

#include <memory>
#include <functional>
#include <string>

namespace Rev
{
	struct TextureData
	{
		int ImageWidth = 0;
		int ImageHeight = 0;
		int ImageChannels = 0;
		int ImageDesiredChannels = 4;
	};

	class Texture
	{
	public:
		Texture(std::string path);
		~Texture();

		TextureData* GetTextureDate() { return m_TextureDate.get(); }
		unsigned char* GetImageData() { return m_ImageData; }

	private:
		void LoadTexture(const char* path);

	private:
		unsigned char* m_ImageData;
		std::unique_ptr<TextureData> m_TextureDate;
	};
}