#pragma once

#include <string>
#include <vector>

namespace RevDev
{
	class ImGuiSetup;
}

namespace RevDev
{
	class UI
	{
	public:
		UI();
		~UI();

		void SubscribeElement(std::string text, float* value);
	private:
		RevDev::ImGuiSetup* m_ImGui;
	};
}