#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../Light/PointLight.hpp"

#include "EnumLightIntensity.hpp"
#include "EnumActiveCamera.hpp"

namespace entity
{
	using namespace light;
	using namespace camera;

	class Player
	{
		public:
			Player();

			void ProcessInput(GLFWwindow* window);
			void Update(float tDeltaTime);
			void Draw();

			CameraData GetCameraData();
			LightData GetPointLightData();

		private:
			void CreateFirstPersonCam();
			void CreateThirdPersonCam();
			const glm::highp_vec3& PointForward();

		private:
			Tank* pTank;
			PointLight* pTankLight;
			PerspectiveCamera* pThirdPersonCam;
			PerspectiveCamera* pFirstPersonCam;

			LampIntensity ECurrentLightIntensity;
			ActiveCamera ECurrentActiveCamera;

		private:
			bool bKey_W;
			bool bKey_S;
			bool bKey_A;
			bool bKey_D;
			bool bKey_Q;
			bool bKey_E;
			bool bKey_F;

			bool bLampToggle;
			bool bCameraToggle;

		private:
			const float fMoveSpeed = 100.0f;
			const float fRotationSpeed = 100.0f;
			const float LOW_INTENSITY = 50.0f;
			const float MID_INTENSITY = 200.0f;
			const float HIGH_INTENSITY = 500.0f;
		
	};
}

#endif // !PLAYER_HPP

