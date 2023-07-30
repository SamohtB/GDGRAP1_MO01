#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../BaseClass/Transform/Transform.hpp"
#include "CameraData.hpp"

namespace camera
{
	using namespace base_class;

	class Camera
	{
		public:
			Camera();

			void SetCamera(glm::vec3 position);
			void MoveCamera(glm::vec3 position);

			void SetCenter(glm::vec3 center);
			void MoveCenter(glm::vec3 center);

			void SetPositionAndCenter(glm::vec3 pos, glm::vec3 center);
			void MovePositionAndCenter(glm::vec3 pos, glm::vec3 center);

			void SetNearPlane(float near);
			void SetFarPlane(float far);

			glm::mat4 GetViewMatrix();
			Transform* GetTransform();

			virtual glm::mat4 GetProjectionMatrix() = 0;
			virtual CameraData GetCameraData() = 0;

		protected:
			const glm::vec3 WORLD_UP = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

			Transform* transform;

			glm::vec3 cameraCenter;
			glm::mat4 view_matrix;
			glm::mat4 projection_matrix;

			float nearPlane;
			float farPlane;
	};

}
#endif // !CAMERA_HPP
