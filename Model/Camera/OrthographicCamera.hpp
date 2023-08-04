#pragma once
#ifndef CAMERA_ORTHOGRAPHIC_CAMERA_HPP
#define CAMERA_ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"

namespace camera
{
	class OrthographicCamera : public Camera
	{
		public:
			OrthographicCamera();

			glm::mat4 GetProjectionMatrix();
			CameraData GetCameraData();

			void SetSize(float size);
			void IncSize(float inc);

			glm::vec3 GetPosition() {return pos;}
			void SetPosition(glm::vec3 pos) {this->pos = pos; }

		private:
			glm::vec3 pos;
			float size;
	};
}
#endif // !CAMERA_ORTHOGRAPHIC_CAMERA_HPP
