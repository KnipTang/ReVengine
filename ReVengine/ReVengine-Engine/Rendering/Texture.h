#pragma once

#include <memory>
#include <functional>

namespace Rev
{
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