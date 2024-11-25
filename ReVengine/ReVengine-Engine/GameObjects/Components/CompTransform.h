#pragma once

#include "GameObjects/BaseComponent.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

namespace Rev
{
	class CompTransform : public BaseComponent
	{
	public:
		CompTransform(GameObject* gameObj, glm::vec3 position = glm::vec3{0,0,0}, glm::vec3 rotation = glm::vec3{ 0, 0, 0 }, glm::vec3 scale = glm::vec3{ 1,1,1 });
		~CompTransform() {};

		void update() override;

		void SetPosition(glm::vec3 pos);
		glm::vec3& GetPosition();
		void SetRotation(glm::vec3 dir);
		glm::vec3& GetRotation();
		glm::mat4 GetModelMatrix();

		glm::vec3 GetForwardVector();
		glm::vec3 GetRightVector();

		void Move(glm::vec3 dir, float speed = 1);
		void MoveForward(int input, float speed = 1);
		void MoveRight(int input, float speed = 1);

		void Turn(float x, float y);
		void AddYawInput(float input);
		void AddPitchInput(float input);
	public:
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale; //TODO

		glm::mat4 m_ModelMatrix;
	};
}