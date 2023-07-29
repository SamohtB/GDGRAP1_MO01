#pragma once
#ifndef BASE_CLASS_TRANSFORM_HPP
#define BASE_CLASS_TRANSFORM_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EnumRotationAxis.hpp"


namespace base_class
{
	class Transform
	{
		public:
			Transform();

			/* Getters */
			glm::vec3 GetPosition();
			glm::vec3 GetForwardVector();
			glm::mat4 GetModelMatrix();
			
			/* Translation Functions */
			void Move(float x, float y, float z);
			void Move(glm::vec3 vector);
			void SetPosition(float x, float y, float z);
			void SetPosition(glm::vec3 vector);

			void SetLocalPosition(float x, float y, float z);
			void SetLocalPosition(glm::vec3 vector);

			/* Rotations Functions */
			void Rotate(RotationAxis axis, float theta);
			void SetRotation(RotationAxis axis, float theta);

			void SetLocalRotation(RotationAxis axis, float theta);

			/* Scale Functions */
			void Scale(float x, float y, float z);
			void Scale(float scalar);
			void Scale(glm::vec3 scalar);

			void SetScale(float x, float y, float z);
			void SetScale(float scalar);
			void SetScale(glm::vec3 scalar);

			void SetLocalScale(float x, float y, float z);
			void SetLocalScale(float scalar);
			void SetLocalScale(glm::vec3 scalar);

		private:
			glm::vec3 position;
			glm::vec3 local_position;
			glm::vec3 scale;
			glm::vec3 local_scale;

			float pitch;
			float yaw;
			float roll;
			float local_pitch;
			float local_yaw;
			float local_roll;
	};
}


#endif