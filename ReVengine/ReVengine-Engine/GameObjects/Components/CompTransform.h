#pragma once

#include "GameObjects/BaseComponent.h"
#include "Utils/Vector3.h"

namespace Rev
{
	class CompTransform : public BaseComponent
	{
	public:
		CompTransform(GameObject* gameObj, Vector3 position = Vector3{0,0,0}, Vector3 rotation = Vector3{ 0,0,0 }, Vector3 scale = Vector3{ 1,1,1 });
		~CompTransform() {};

		void update() override; // override is not requered to override a virtual funciton from base class, but its good practice

		void setPosition(Vector3 pos);
		Vector3 getPosition();

	public:
		Vector3 m_Position;
		Vector3 m_Rotation;
		Vector3 m_Scale;
	private:
	};
}