#pragma once

#include "GameObjects/BaseComponent.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/quaternion.hpp>

namespace Rev
{
	class CompTransform : public BaseComponent
	{
	public:
		CompTransform(GameObject* gameObj, glm::vec3 position = glm::vec3{0,0,0}, glm::quat rotation = glm::quat{ 0, 0, 0, 0 }/*, Vector3 scale = Vector3{ 1,1,1 }*/);
		~CompTransform() {};

		void update() override;

		void SetPosition(glm::vec3 pos);
		glm::vec3& GetPosition();
		void SetRotation(glm::quat dir);
		glm::quat& GetRotation();
		glm::mat4 GetWorldMatrix();

		glm::vec3 GetForwardVector();
		glm::vec3 GetRightVector();

		void Move(glm::vec3 dir, float speed = 1);
		void MoveForward(int input, float speed = 1);
		void MoveRight(int input, float speed = 1);

		void Turn(float x, float y);
		void AddYawInput(float input);
		void AddPitchInput(float input);
	public:
		glm::vec3 m_Position;
		glm::quat m_Rotation;

		glm::mat4 m_WorldMatrix;
		//Vector3 m_Scale; //TODO
	private:
	};
}