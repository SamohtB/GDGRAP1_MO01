#pragma once
#ifndef CAMERA_PERSPECTIVE_CAMERA_HPP
#define	CAMERA_PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"
#include "../../Config/Settings.hpp"

namespace camera
{
	class PerspectiveCamera : public Camera
	{
		public:
			PerspectiveCamera();

			glm::mat4 GetProjectionMatrix();
			CameraData GetCameraData();

			void SetFOV(float FOV);
			void IncFOV(float inc);

		private:
			const float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
			float FOV;
	};
}

#endif // !CAMERA_PERSPECTIVE_CAMERA_HPP
