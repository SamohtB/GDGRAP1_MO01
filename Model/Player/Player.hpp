#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../Light/PointLight.hpp"

namespace entity
{
	using namespace light;
	using namespace camera;

	class Player
	{
		public:
			Player();

			void CreateLight();

			void ProcessInput(GLFWwindow* window);
			void Update(float tDeltaTime);
			void Draw();

			CameraData GetCameraData();
			LightData GetPointLightData();

		private:
			Tank* pTank;
			PointLight* pTankLight;
			PerspectiveCamera* pTankCamera;

		private:
			bool bKey_W;
			bool bKey_S;
			bool bKey_A;
			bool bKey_D;
			bool bKey_Q;
			bool bKey_E;
			bool bKey_F;

		private:
			const float fMoveSpeed = 100.0f;
			const float fRotationSpeed = 100.0f;

	};
}

#endif // !PLAYER_HPP

