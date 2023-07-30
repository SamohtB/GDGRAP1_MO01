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

		private:
			float size;
	};
}
#endif // !CAMERA_ORTHOGRAPHIC_CAMERA_HPP
