#include "ResourceManager.h"
#include "Rendering/Texture.h"
#include <SDL_messagebox.h>

using namespace RevDev;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

Rev::Texture* ResourceManager::LoadResource(std::string name, std::string path)
{
	auto it = m_LoadedResources.find(name);
	if (it != m_LoadedResources.end()) //Check if inside of loadedResources
	{
		return it->second;
	}
	else
	{
		Rev::Texture* newTexture = new Rev::Texture{ path };
		auto newResource = m_LoadedResources.emplace(name, newTexture);
		return newResource.first->second;
	}
	return nullptr;
}

Rev::Texture* ResourceManager::GetResource(std::string name)
{
	auto it = m_LoadedResources.find(name);
	if (it != m_LoadedResources.end()) //Check if inside of loadedResources
		return it->second;
	else
	{
		std::string message = "Texture \"" + name + "\" not found!";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Resource Manager", message.c_str(), nullptr);
	}
	return nullptr;
}