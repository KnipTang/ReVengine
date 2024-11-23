#pragma once

#include "GameObjects/BaseComponent.h"
#include "Utils/Vector3.h"

namespace Rev
{
	class CompTransform : public BaseComponent
	{
	public:
		CompTransform(GameObject* gameObj, Vector3 position = Vector3{0,0,0}, Vector3 rotation = Vector3{ 0,0,0 }/*, Vector3 scale = Vector3{ 1,1,1 }*/);
		~CompTransform() {};

		void update() override;

		void SetPosition(Vector3 pos);
		Vector3 GetPosition();

		Vector3 GetForwardVector();
		Vector3 GetRightVector();

		void Move(Vector3 dir, float speed = 1);
		void MoveForward(int input, float speed = 1);
		void MoveRight(int input, float speed = 1);

	public:
		Vector3 m_Position;
		Vector3 m_Rotation;
		//Vector3 m_Scale; //TODO
	private:
	};
}