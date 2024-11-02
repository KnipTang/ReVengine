#pragma once

namespace Rev
{
	class BaseComponent
	{
	public:
		virtual void update() = 0; // = 0 means pure virtual // If function is not pure virtual it has the option of being overriten. Pure function have to be overritten

	private:
	};
}