#pragma once

#include <memory>

namespace Rev
{
	class GameObject;
}

namespace Rev
{
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* gameObj);
		virtual ~BaseComponent() = default;

		virtual void update() {}; // = 0 means pure virtual // If function is not pure virtual it has the option of being overriten. Pure function have to be overritten
		virtual void fixedUpdate() {};
		virtual const void render() {};
	private:
		GameObject* m_GameObject;
	};
}