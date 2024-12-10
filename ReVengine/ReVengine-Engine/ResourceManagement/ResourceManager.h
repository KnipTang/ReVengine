#pragma once
#include <unordered_map>
#include <string>

namespace Rev
{
	class Texture;
}

namespace RevDev
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		Rev::Texture* LoadResource(std::string name, std::string path);

		Rev::Texture* GetResource(std::string name);

	private:
		std::unordered_map<std::string, Rev::Texture*> m_LoadedResources;
	};
}