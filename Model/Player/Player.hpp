#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../Light/PointLight.hpp"
#include "EnumLightIntensity.hpp"

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
			Tank* pTank;
			PointLight* pTankLight;
			PerspectiveCamera* pTankCamera;

			LampIntensity ECurrentLightIntensity;

		private:
			bool bKey_W;
			bool bKey_S;
			bool bKey_A;
			bool bKey_D;
			bool bKey_Q;
			bool bKey_E;
			bool bKey_F;
			bool bLampToggle;

		private:
			const float fMoveSpeed = 100.0f;
			const float fRotationSpeed = 100.0f;
			const float LOW_INTENSITY = 50.0f;
			const float MID_INTENSITY = 200.0f;
			const float HIGH_INTENSITY = 500.0f;

	private:
		const LightData startLightData
		{
			light_position = glm::vec3(0.0f, 0.0f, 0.0f),
			light_color = glm::vec3(1.0f, 1.0f, 1.0f),
			ambient_color = glm::vec3(1.0f, 1.0f, 1.0f),
			ambient_str = 0.2f,
			spec_str = 0.5f,
			spec_phong = 16.0f,
			intensity = LOW_INTENSITY
		}
	};
}

#endif // !PLAYER_HPP

